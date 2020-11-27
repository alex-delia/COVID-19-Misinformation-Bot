#include <iostream>
#include "include/curl/curl.h"
#include "twitter.h"
#include "covid.h"
#include "covidStats.h"
using namespace std;

void flagTweet(Twitter t){

    string hashtags[3] = {"covidisahoax", "masksdontwork", "covidisfake"};

    int index = rand() % 3; 

    string tweetId = t.getTweet(hashtags[index]);

    string userName = t.getSenderOfTweet( tweetId);

    t.sendReply(".@" + userName + ", This tweet has a claim or hashtag that contains misinformation!\nStay up to date on COVID-19 Facts and Regulations at https://www.cdc.gov/", tweetId);

}

int main()
{
    Twitter twit = Twitter();
    Twitter twit_flag = Twitter();
    string worldData = Covid::getWorldData();

    string canadaTests = covidStats::getCanadaTests();


    cout << "Flagging Tweet" << endl;

    flagTweet(twit_flag);

    cout << "Posting Case Count Tweet" << endl;

    twit.sendTweet("There were " + worldData + " cases of COVID-19 today, globally");
    twit.sendTweet("There were " + canadaTests + " COVID-19 tests performed today in Canada");

}
