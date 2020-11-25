#include <iostream>
#include "twitterClient.h"
using namespace std;

class Twitter {
    public:
        Twitter();
        void sendTweet(string input);
        void sendReply(string input, string id);
        string getTweet(string input);
        string getSenderOfTweet(string id);
        bool isRetweet(string id);
        bool isQuote(string id);
    private:
        twitCurl twit;
};