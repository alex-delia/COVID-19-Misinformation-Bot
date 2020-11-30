#include <iostream>
#include "include/curl/curl.h"
#include "twitter.h"
#include "covid.h"
#include "newsArticles.h"
using namespace std;

void flagTweet(Twitter t){

    string hashtags[10] = {"covidisahoax", "masksdontwork", "covidisfake", "nomasks","plandemic", "scamdemic","masksdontwork","nomaskmandates","nonewnormal", "covidhoax"};

    int index = rand() % 10; 
    string newsArticles;
    string tweetId = t.getTweet(hashtags[index]);

    string userName = t.getSenderOfTweet( tweetId);

    if (index == 0 || index == 2 || index == 4 ||index == 5 ||index == 8 ||index == 9){
        newsArticles = "https://www.cdc.gov/coronavirus/2019-ncov/index.html";
    }
    else {
        newsArticles = "https://www.cdc.gov/coronavirus/2019-ncov/prevent-getting-sick/diy-cloth-face-coverings.html";
    }

    string tweet = ".@" + userName + ", This tweet has a claim or hashtag that contains misinformation!\nMake sure you are getting all of your facts from a trusted source. You can read more on this subject here: "+ newsArticles;

    t.sendReply(tweet, tweetId);

}

int main()
{
    Twitter twit = Twitter();

    Twitter twit_tests = Twitter();
    Twitter twit_deaths_recoveries = Twitter();

    Twitter twit_flag = Twitter();

    string worldData = covid::getWorldData();
    string canadaTests = covid::getCanadaTests();
    string canadaDeaths = covid::getCanadaDeaths();
    string canadaRecoveries = covid::getCanadaRecoveries();
    string newsArticles = NewsArticles::getNewsArticles("covid");


    cout << "Flagging Tweet" << endl;

    flagTweet(twit_flag);

    cout << "Posting Case Count Tweet" << endl;

    twit.sendTweet("There were " + worldData + " cases of COVID-19 today, globally");
    twit_tests.sendTweet("There were " + canadaTests + " COVID-19 tests performed today in Canada");
    twit_deaths_recoveries.sendTweet("There were " + canadaDeaths + " COVID-19 deaths and " + canadaRecoveries + " COVID-19 recoveries today in Canada");
    twit.sendTweet("Check out this article: "+ newsArticles); //new

}
