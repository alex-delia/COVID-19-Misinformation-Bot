#include <iostream>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "json.hpp"
#include <typeinfo>
#include "newsArticles.h"

using json = nlohmann::json;
using namespace std;


/**
 * newsArticles.h/newsArticles.cpp
 * 
 * @brief This class uses libcurl to get information from the NewsAPI 
 * @author Janki Chaudhari (251004226)
 * 
 * This class uses libcurl which fetches information from News API gets the latest news in canada 
 * corrosponding to the key word.
 */

/** @brief gets the size of the data from the GET request made by curl
* @param ptr returned data pointer
* @param size size of the data item
* @param count the number of the data items
* @param stream pointer to store the data
* @return the number of bytes that the data is (unsized integral type)
* A callback function called by libcurl so that the received data can be collected in a single buffer
*/
size_t NewsArticles::write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
return size*count;
}


/**
 * the Constructor fetches articles from the news API coorosponding to a particular tweet and returns it to main 
 * @param hashtag gets the associated hashtag from the tweet and gets the corrosponding articles
 * @return url to the most relevant news article from the NewsAPI 
**/
string NewsArticles::getNewsArticles(string hashtag)
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  //uses the newsapi to get the articles, and retrive related articles from canada 
  const string articles = "https://newsapi.org/v2/top-headlines?country=ca&q="+hashtag+"&sortby=relevancy&apiKey=e22951bfb276477bafc045510504e534"; 
  if(curl) {
    string response;
    curl_easy_setopt(curl, CURLOPT_URL,articles.c_str());  //calls the api 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string); //converts json to string 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); 

    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);

    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    /* always cleanup */ 
    curl_easy_cleanup(curl);

    json j = json::parse(response);  // parse the response 
    
   return to_string(j["articles"][1]["url"]);  // returns the link to the news articles 
    
  }
  return "NULL";
}