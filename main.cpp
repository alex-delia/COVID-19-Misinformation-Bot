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
        string newsArticles = NewsArticles::getNewsArticles("covid");
    }
    else {
        string newsArticles = NewsArticles::getNewsArticles("mask");
    }


    t.sendReply(".@" + userName + ", This tweet has a claim or hashtag that contains misinformation!\nStay up to date on COVID-19 Facts and Regulations at https://www.cdc.gov/. You can read more at: "+ newsArticles, tweetId);

}

int main()
{
    Twitter twit = Twitter();

    Twitter twit_tests = Twitter();
    Twitter twit_deaths_recoveries = Twitter();

    Twitter twit_flag = Twitter();

    string worldData = covid::getWorldData();
    string canadaDeaths = covid::getCanadaDeaths();
    string canadaRecoveries = covid::getCanadaRecoveries();
    string newsArticles = NewsArticles::getNewsArticles("covid");

    string ONTests = covid::getTests("ON");
    string QCTests = covid::getTests("QC");
    string BCTests = covid::getTests("BC");
    string ABTests = covid::getTests("AB");
    string SKTests = covid::getTests("SK");
    string MNTests = covid::getTests("MN");
    string NSTests = covid::getTests("NS");
    string NBTests = covid::getTests("NB");
    string PEITests = covid::getTests("PE");
    string NLTests = covid::getTests("NL");
    string NTTests = covid::getTests("NT");
    string YKTests = covid::getTests("YK");
    string NUTests = covid::getTests("NU");


    cout << "Flagging Tweet" << endl;

    flagTweet(twit_flag);

    cout << "Posting Case Count Tweet" << endl;

    twit.sendTweet("There were " + worldData + " cases of COVID-19 today, globally");

    twit_tests.sendTweet("Daily Province Change in Covid Testing:\nON: " + ONTests + "\nQC: " + QCTests + "\nBC: " + BCTests + "\nAB: " 
    + ABTests + "\nSK: " + SKTests + "\nMN: " + MNTests + "\nNS: " + NSTests + "\nNB: " + NBTests + "\nPEI: " + PEITests 
    + "\nNL: " + NLTests + "\nNT: " + NTTests + "\nYK: " + YKTests + "\nNU: " + NUTests);


    twit_deaths_recoveries.sendTweet("There were " + canadaDeaths + " COVID-19 deaths and " + canadaRecoveries + " COVID-19 recoveries today in Canada");
    twit.sendTweet("Check out this article: "+ newsArticles); //new

}
