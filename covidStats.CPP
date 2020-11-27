#include <iostream>
#include "covidStats.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "json.hpp"

// for convenience
using json = nlohmann::json;
using namespace std;

size_t covidStats::write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
return size*count;
}

string covidStats::getCanadaTests()
{
  
  CURL *curl;
  CURLcode response;
 
  curl = curl_easy_init();

  if(curl) {
    string parsedResponse;
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.covid19tracker.ca/summary");
    // curl_easy_setopt(curl, CURLOPT_URL, "https://api.covid19api.com/summary");
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
    
    return j["data"][0]["change_tests"];
   
  }
  return 0;
}