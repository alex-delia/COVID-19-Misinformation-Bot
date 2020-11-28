#include <iostream>
#include "newsArticles.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "json.hpp"
#include <typeinfo>

// for convenience
using json = nlohmann::json;
using namespace std;

size_t NewsArticles::write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
return size*count;
}
string NewsArticles::getNewsArticles(string hashtag)
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  const string articles = "https://newsapi.org/v2/top-headlines?country=ca&q="+hashtag+"&sortby=relevancy&apiKey=e22951bfb276477bafc045510504e534"; 
  if(curl) {
    string response;
    curl_easy_setopt(curl, CURLOPT_URL,articles.c_str());
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
    
   return to_string(j["articles"][1]["url"]);
    
  }
  return "NULL";
}