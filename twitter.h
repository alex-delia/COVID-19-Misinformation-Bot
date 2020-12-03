#include <iostream>
#include "twitterClient.h"
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

class Twitter {
    public:
        Twitter();
        void sendTweet(string input);
        void sendReply(string input, string id);
        string getTweet(string input);
        string getSenderOfTweet(string id);
        bool isRetweet(string id);
       
    private:
        twitCurl twit;
};