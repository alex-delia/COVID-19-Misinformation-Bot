#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "twitter.h"
#include "json.hpp"
#include <typeinfo>

using json = nlohmann::json;
using namespace std;

Twitter::Twitter(){
    this->twit.getOAuth().setConsumerKey("ulNuJWQiUBVUn9XV2SawRQwDg");
    this->twit.getOAuth().setConsumerSecret("ArkIXUoHL9CiGZV9AsbZFbiWc4TMMEUFwd91tlVFMRhhJaiV1h");
    this->twit.getOAuth().setOAuthTokenKey("1324153496338354179-1hlRx3AkUwCRB2ptynR3dqYQgA5Usb");
    this->twit.getOAuth().setOAuthTokenSecret("os0Y2gCaoigZD0x6Q1w6HQHbPXhQE9qqQqtPJnxqq5VwJ");
}

void Twitter::sendTweet(string input)
{
    string resp;

    //Send API Call
    if(this->twit.statusUpdate(input)){
        this->twit.getLastWebResponse(resp);
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", resp.c_str() );
    }
    else
    {
        this->twit.getLastCurlError( resp );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }

}

void Twitter::sendReply(string input, string id)
{
    string resp;

    cout << id << endl;
    //Send API Call
    if(this->twit.statusUpdate( input, id )){
        this->twit.getLastWebResponse(resp);
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", resp.c_str() );
    }
    else
    {
        this->twit.getLastCurlError( resp );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }

}

string Twitter::getSenderOfTweet(string id)
{
    string resp;
    cout << id << endl;

    //Send API Call
    if(this->twit.statusShowById(id )){
        this->twit.getLastWebResponse(resp);

        json j = json::parse(resp);
        return j["user"]["screen_name"];
    }
    else
    {
        this->twit.getLastCurlError( resp );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }

}

bool Twitter::isRetweet(string id)
{
    string resp;

    //Send API Call
    if(this->twit.statusShowById(id)){
        this->twit.getLastWebResponse(resp);

        json j = json::parse(resp);

        return !j["retweeted_status"].is_null();
    }
    else
    {
        this->twit.getLastCurlError( resp );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }
}

string Twitter::getTweet(string input)
{
    string resp = "";

    //Send API Call
    if( this->twit.search(input, "10") )
    {
        this->twit.getLastWebResponse( resp );

        json j = json::parse(resp);

        for(int i = 0; i < 10; i++){
            string id = to_string(j["statuses"][i]["id"]);
            if (!isRetweet(id)){
                return id;
            }
        }

        return "0";
    }
    else
    {
        this->twit.getLastCurlError( resp );
        printf( "\ntwitterClient:: twitCurl::search error:\n%s\n", resp.c_str() );
        return "";
    }
}