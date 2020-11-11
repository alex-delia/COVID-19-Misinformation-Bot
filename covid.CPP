#include <iostream>
#include "covid.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "json.hpp"
#include <typeinfo>

// for convenience
using json = nlohmann::json;
using namespace std;

size_t Covid::write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
return size*count;
}

string Covid::getWorldData()
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
  return "NULL";
}