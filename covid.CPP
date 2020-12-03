#include <iostream>
#include "covid.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <ctime>
#include "json.hpp"
#include <typeinfo>

// for convenience
using json = nlohmann::json;
using namespace std;

size_t covid::write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
return size*count;
}

/** @brief gets the world Covid-19 summary
   *  @return returns an string containing the new confirmed daily cases in the world
   * 
   * Calls Covid-19 API URL using curl to fetch the world summary data
   * The json is then parsed to return the confirmed new cases
   */
string covid::getWorldData()
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();

  if(curl) {
    string response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.covid19api.com/summary");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);

    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    /* always cleanup */ 
    curl_easy_cleanup(curl);

    json j = json::parse(response);

    return to_string(j["Global"]["NewConfirmed"]);
    }

    return 0;
  }

  /** @brief gets the Canada Covid-19 summary
   *  @return returns an json containing the Canada Covid-19 data
   * 
   * Calls Canadian Covid-19 API URL using curl to fetch the summary data
   * This json is then returned for further use within other functions
   */
  json covid::getCanadaData()
  {
  
  CURL *curl;
  CURLcode response;
 
  curl = curl_easy_init();

  if(curl) {
    string parsedResponse;
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.covid19tracker.ca/summary");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &parsedResponse);

    /* Perform the request, response will get the return code */ 
    response = curl_easy_perform(curl);

    /* Check for errors */ 
    if(response != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(response));

    /* always cleanup */ 
    curl_easy_cleanup(curl);

    json j = json::parse(parsedResponse);
    
    return j;

    }
    return NULL;
  }

  /** @brief gets the daily COVID-19 tests per province
   *  @param province a string containing the code for a province
   *  @return returns a string containing the daily tests in the specified province
   * 
   * Uses C++ time functions to get yesterdays date
   * This date is inputted into the Canadian Covid-19 API URL using curl to fetch the data
   * The json is then parsed to get the daily tests from the data 
   */
  string covid::getTests(string province)
  {
  
  CURL *curl;
  CURLcode response;
 
  curl = curl_easy_init();

  if(curl) {
    string parsedResponse;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    string currentDate;
    ltm->tm_mday = 1;
    ltm->tm_mon = 10;

    if(ltm->tm_mday != 1)
      currentDate = to_string(ltm->tm_year + 1900) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday-1);
    else
    {
      int month;
      int day;

      if(ltm->tm_mon+1 == 1)
        month = 12;
      else
        month = ltm->tm_mon;

      switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
          day = 31;
          break;

        case 4:
        case 6:
        case 9:
        case 11:
          day = 30;
          break;

        case 2:
          int year = ltm->tm_year + 1900;
          if (((year % 4 == 0) && !(year % 100 == 0))|| (year % 400 == 0))
            day = 29;
          else
            day = 28;
      }

      currentDate = to_string(ltm->tm_year + 1900) + "-" + to_string(month) + "-" + to_string(day);
    }
    
    string apiURL = "https://api.covid19tracker.ca/reports/province/"+province+"?fill_dates&stat&date="+currentDate+"&after&before";

    curl_easy_setopt(curl, CURLOPT_URL, apiURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &parsedResponse);

    /* Perform the request, response will get the return code */ 
    response = curl_easy_perform(curl);

    /* Check for errors */ 
    if(response != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(response));

    /* always cleanup */ 
    curl_easy_cleanup(curl);

    json j = json::parse(parsedResponse);
    
    return to_string(j["data"][0]["change_tests"]);

    }
    return NULL;
  }

  /** @brief gets the total recoveries on the current date
   *  @return returns an int containing the total recoveries to the current date
   * 
   * Uses C++ time functions to get current date
   * This date is inputted into the Canadian Covid-19 API URL using curl to fetch the data
   * The json is then parsed to get the totalRecoveries from the data 
   */
  int covid::getDailyTotalRecovs()
  {
  
  CURL *curl;
  CURLcode response;
 
  curl = curl_easy_init();

  if(curl) {
    string parsedResponse;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    string currentDate = to_string(ltm->tm_year + 1900) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday);
    
    string apiURL = "https://api.covid19tracker.ca/reports?fill_dates&stat&date="+currentDate+"&after&before";

    curl_easy_setopt(curl, CURLOPT_URL, apiURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &parsedResponse);

    /* Perform the request, response will get the return code */ 
    response = curl_easy_perform(curl);

    /* Check for errors */ 
    if(response != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(response));

    /* always cleanup */ 
    curl_easy_cleanup(curl);

    json j = json::parse(parsedResponse);
    
    return j["data"][0]["total_recoveries"];
    }
    return 0;
  }


  /** @brief gets the total recoveries a week ago from the current date
   *  @return returns an int containing the total recoveries from one week ago
   * 
   * Uses C++ time functions to get current date, and then properly find the date 7 days prior
   * This date is inputted into the Canadian Covid-19 API URL using curl to fetch the data
   * The json is then parsed to get the totalRecoveries from the data 
   */
  int covid::getLastWeekRecovs()
  {
  
  CURL *curl;
  CURLcode response;
 
  curl = curl_easy_init();

  if(curl) {
    string parsedResponse;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    string weekAgo;

    if(ltm->tm_mday > 7)
      weekAgo = to_string(ltm->tm_year + 1900) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday-7);
    else
    {
      int month;
      int day = ltm->tm_mday;

      if(ltm->tm_mon+1 == 1)
        month = 12;
      else
        month = ltm->tm_mon;

      switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
          day = 31 - (7-day);
          break;

        case 4:
        case 6:
        case 9:
        case 11:
          day = 30 - (7-day);
          break;

        case 2:
          int year = ltm->tm_year + 1900;
          if (((year % 4 == 0) && !(year % 100 == 0))|| (year % 400 == 0))
            day = 29 - (7-day);
          else
            day = 28 - (7-day);
      }

      weekAgo = to_string(ltm->tm_year + 1900) + "-" + to_string(month) + "-" + to_string(day);
    }
    
    string apiURL = "https://api.covid19tracker.ca/reports?fill_dates&stat&date="+weekAgo+"&after&before";

    curl_easy_setopt(curl, CURLOPT_URL, apiURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &parsedResponse);

    /* Perform the request, response will get the return code */ 
    response = curl_easy_perform(curl);

    /* Check for errors */ 
    if(response != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(response));

    /* always cleanup */ 
    curl_easy_cleanup(curl);

    json j = json::parse(parsedResponse);
    
    return j["data"][0]["total_recoveries"];
    }
    return 0;
  }


  /** @brief parses a json to get daily deaths
   *  @return returns a string containing the number of daily deaths
   * 
   * Calls the getCanadaData() function to get a json containing data, then parses through the json to get the daily deaths 
   * in a string
   */
  string covid::getCanadaDeaths()
  {
    json j = getCanadaData();

    if(j == NULL)
      return NULL;
    else
      return j["data"][0]["change_fatalities"];
  }

  /** @brief parses a json to get daily recoveries
   *  @return returns a string containing the number of daily recoveries
   * 
   * Calls the getCanadaData() function to get a json containing data, then parses through the json to get the daily recoveries
   * in a string
   */
  string covid::getCanadaRecoveries()
  {
    json j = getCanadaData();

    if(j == NULL)
      return NULL;
    else
      return j["data"][0]["change_recoveries"];

  }
  
  
  

  