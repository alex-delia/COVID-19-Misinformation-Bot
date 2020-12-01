#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "twitter.h"
#include "json.hpp"
#include <typeinfo>

using json = nlohmann::json;
using namespace std;

/**
 * Twitter.h/Twitter.cpp
 * 
 * @brief This class communicates with the twitcurl library and Twitter API to provide a variety of relevant methods
 * 
 * @author Finn Ferguson (251026399)
 * 
 * This class uses the twitcurl library which communicates to the Twitter API to execute all of the important twitter functions. This includes searching, replying
 * and posting tweets. Aswell there are some boolean methods to check the characteristics of a given tweet. All of these are extremely important to geting the bot to 
 * run correctly.
 */

/**
 * Constructs basic twitter object and sets all the proper authentication tokens so we can make calls to the API
 */
Twitter::Twitter(){
    this->twit.getOAuth().setConsumerKey("ulNuJWQiUBVUn9XV2SawRQwDg");
    this->twit.getOAuth().setConsumerSecret("ArkIXUoHL9CiGZV9AsbZFbiWc4TMMEUFwd91tlVFMRhhJaiV1h");
    this->twit.getOAuth().setOAuthTokenKey("1324153496338354179-1hlRx3AkUwCRB2ptynR3dqYQgA5Usb");
    this->twit.getOAuth().setOAuthTokenSecret("os0Y2gCaoigZD0x6Q1w6HQHbPXhQE9qqQqtPJnxqq5VwJ");
}

/**
 * sends a tweet for the twitter bot to post
 * 
 * @param input the text to be contained in the tweet
 */

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

/**
 * replies to any given tweet using the twitter bot
 * 
 * @param input the text to be contained in the reply
 * @param id the id of the tweet you wish to reply to
 */
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

/**
 * retrieves the handle of user who posted any given tweet
 * 
 * @param id the id of the tweet you wish to find the sender of
 * @return the twitter handle of the user who posted the tweet, contained in a string
 */
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

/**
 * checks if a tweet is a retweet, as supposed to a quote tweet or a normal tweet
 * 
 * @param id the id of the tweet in question
 * @returns boolean containing whether or not the tweet is a retweet
 */
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

/**
 * searches for a relevant tweet based on some query. returns the first tweet that is not a retweet.
 * 
 * @param input string used to query for tweets 
 * @returns the id of the found tweet
 */
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
                cout << "Tweet: " << j["statuses"][i]["text"] << endl;
                cout << "ID: " << to_string(j["statuses"][i]["id"]) << endl;
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