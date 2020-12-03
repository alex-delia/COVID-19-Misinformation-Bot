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
 * @brief Constructs basic twitter object
 * 
 * Constructs basic twitter object and sets all the proper authentication tokens so we can make calls to the API
 */
Twitter::Twitter(){
    this->twit.getOAuth().setConsumerKey("ulNuJWQiUBVUn9XV2SawRQwDg"); //Sets Consumer Key
    this->twit.getOAuth().setConsumerSecret("ArkIXUoHL9CiGZV9AsbZFbiWc4TMMEUFwd91tlVFMRhhJaiV1h"); //Sets Consumer Secret
    this->twit.getOAuth().setOAuthTokenKey("1324153496338354179-1hlRx3AkUwCRB2ptynR3dqYQgA5Usb"); //Sets Token Key for OAuth
    this->twit.getOAuth().setOAuthTokenSecret("os0Y2gCaoigZD0x6Q1w6HQHbPXhQE9qqQqtPJnxqq5VwJ"); //Sets Token Secret for OAuth
}

/**
 * @brief sends a tweet for the twitter bot to post
 * 
 * Using Twitter API, the bot tweets the text given in the method.
 * 
 * @param input the text to be contained in the tweet
 */

void Twitter::sendTweet(string input)
{
    string resp;

    //Send API Call
    if(this->twit.statusUpdate(input)){ //Calls endpoint to send a tweet out
        this->twit.getLastWebResponse(resp); //Gets success response from API
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", resp.c_str() );
    }
    else
    {
        this->twit.getLastCurlError( resp ); //Gets failure response from API
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }

}

/**
 * @brief replies to any given tweet using the twitter bot
 * 
 * Using the Twitter API, the bot replies to the tweet with the ID given
 * 
 * @param input the text to be contained in the reply
 * @param id the id of the tweet you wish to reply to
 */
void Twitter::sendReply(string input, string id)
{
    string resp;

    cout << id << endl;
    //Send API Call
    if(this->twit.statusUpdate( input, id )){ //Calls endpoint to send reply
        this->twit.getLastWebResponse(resp); //Gets success response from API
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", resp.c_str() );
    }
    else
    {
        this->twit.getLastCurlError( resp ); //Gets failure response from API
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }

}

/**
 * @brief retrieves the handle of user who posted any given tweet
 * 
 * Using the Twitter API, this method finds the tweet with the given ID and returns the handle of the user who tweeted it.
 * 
 * @param id the id of the tweet you wish to find the sender of
 * @return the twitter handle of the user who posted the tweet, contained in a string
 */
string Twitter::getSenderOfTweet(string id)
{
    string resp;
    cout << id << endl;

    //Send API Call
    if(this->twit.statusShowById(id )){ //Calls endpoint to get tweet
        this->twit.getLastWebResponse(resp); //assigns resp to the API response
            
        json j = json::parse(resp); //Parses reponse into JSON
        return j["user"]["screen_name"];
    }
    else
    {
        this->twit.getLastCurlError( resp ); //Gets failure response from API
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }

}

/**
 * @brief checks if a tweet is a retweet
 * 
 * Since a retweet cannot be replied to, this method checks if the tweet is a retweet.
 * 
 * @param id the id of the tweet in question
 * @returns boolean containing whether or not the tweet is a retweet
 */
bool Twitter::isRetweet(string id)
{
    string resp;

    //Send API Call
    if(this->twit.statusShowById(id)){ //Calls endpoint to get tweet
        this->twit.getLastWebResponse(resp); //assigns resp to the API response

        json j = json::parse(resp); //parses repsonse into JSON

        return !j["retweeted_status"].is_null();
    }
    else
    {
        this->twit.getLastCurlError( resp ); //Gets failure resp from API
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }
}

/**
 * @brief searches for a relevant tweet based on some query
 * 
 * Uses the Twitter API to search for the most recent tweet that matches the query, also ignores any retweets.
 * 
 * @param input string used to query for tweets 
 * @returns the id of the found tweet
 */
string Twitter::getTweet(string input)
{
    string resp = "";

    //Send API Call
    if( this->twit.search(input, "10") ) //Searches for tweet with API call
    {
        this->twit.getLastWebResponse( resp ); //gets response and assigns it to resp


        json j = json::parse(resp); //parses response into JSON

        for(int i = 0; i < 10; i++){ //loops through all the tweets in response

            string id = to_string(j["statuses"][i]["id"]); //gets ID of current tweet

            if (!isRetweet(id)){ //checks if current tweet isn't a retweet

                cout << "Tweet: " << j["statuses"][i]["text"] << endl;
                cout << "ID: " << to_string(j["statuses"][i]["id"]) << endl;

                return id; //returns the ID if it isn't
            }
        }

        return "0";
    }
    else
    {
        this->twit.getLastCurlError( resp ); //Gets failure response from API
        printf( "\ntwitterClient:: twitCurl::search error:\n%s\n", resp.c_str() );
        return "";
    }
}