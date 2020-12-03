/************************************************
 The main class to run the twitter bot
 ***********************************************/

/// Libraries included
#include <iostream>
#include "include/curl/curl.h"
#include "twitter.h"
#include "covid.h"
#include "newsArticles.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

//! Method to flag and respond to posts
/** 
 * @brief The flagTweet method takes a tweet that contains one of the 10 defined hashtags and 
 * reponds to it using official links to trusted COVID-19 information
 * @param t the twitter object that allows the bot to run
 * @author Estelle Chung 
 * 
*/
void flagTweet(Twitter t){

    string hashtags[10] = {"covidisahoax", "masksdontwork", "covidisfake", "nomasks","plandemic", "scamdemic","masksdontwork","nomaskmandates","nonewnormal", "covidhoax"}; /*!< fake news COVID-19 hashtags */

    int index = rand() % 10; /*!< 1-10 index number*/

    string newsArticles; /*!< news article URL */

    string tweetId = t.getTweet(hashtags[index]); /*!< the tweet ID */

    string userName = t.getSenderOfTweet( tweetId); /*!< the tweeter's username (handle) */

    //! Loop to find relevent news article URL
    /*!
      Depending on the category of hashtag (general COVID-19 or masks), an approriate URL is returned
    */
    if (index == 0 || index == 2 || index == 4 ||index == 5 ||index == 8 ||index == 9){ /*!< general COVID-19 URL */
        newsArticles = "https://www.cdc.gov/coronavirus/2019-ncov/index.html";
    }
    else {
        newsArticles = "https://www.cdc.gov/coronavirus/2019-ncov/prevent-getting-sick/diy-cloth-face-coverings.html"; /*!< mask related URL*/
    }

    string tweet = ".@" + userName + ", This tweet has a claim or hashtag that contains misinformation!\nMake sure you are getting all of your facts from a trusted source. You can read more on this subject here: "+ newsArticles; /*!< creates reply to be posted */

    t.sendReply(tweet, tweetId); /*!< tweet the reply */
}

/** @brief Posts a new tweet to twitter
   * @author Alex 
   * Uses the province based covid functions to retrieve data, then creates a new twitter object and sends out a tweet
   */
void postProvinces(){
    Twitter twit_tests = Twitter(); /*!< set up twitter bot for posting about COVID-19 tests */

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

    twit_tests.sendTweet("Daily Province Change in Covid Testing:\nON: " + ONTests + "\nQC: " + QCTests + "\nBC: " + BCTests + "\nAB: " 
    + ABTests + "\nSK: " + SKTests + "\nMN: " + MNTests + "\nNS: " + NSTests + "\nNB: " + NBTests + "\nPEI: " + PEITests 
    + "\nNL: " + NLTests + "\nNT: " + NTTests + "\nYK: " + YKTests + "\nNU: " + NUTests);
}
//! Main
/**
 *  @author Estelle Chung
 *  @brief Main method to create the twitter bot and post daily updates
 *  In the main method, the Twitter bot is created and all the COVID-19 information is received. 
 *  The flag tweet method is called to flag a tweet daily, 
 *  and then the bot posts daily updates for COVID-19 data about cases, recoveries and deaths.
 * 
*/
int main()
{
    Twitter twit = Twitter(); /*!< set up twitter bot */

    Twitter twit_deaths_recoveries = Twitter(); /*!< set up twitter bot for posting about COVID-19 deaths & recoveries */

    Twitter twit_flag = Twitter(); /*!< set up twitter bot for flagging tweets */

    string worldData = covid::getWorldData(); /*!< COVID-19 data from around the world*/

    string canadaDeaths = covid::getCanadaDeaths(); /*!< COVID-19 deaths in Canada */

    string canadaRecoveries = covid::getCanadaRecoveries(); /*!< COVID-19 recoveries in Canada */

    string newsArticles = NewsArticles::getNewsArticles("covid"); /*!< set up news articles based on the keyword "covid" */

    cout << "Flagging Tweet" << endl; /*!< output notifying flagging a tweet */

    try {
        flagTweet(twit_flag); /*!< call flag tweet method */
    } catch (json::exception e){

    }

    cout << "Posting Case Count Tweet" << endl; /*!< output notifying daily posts */

    twit.sendTweet("There were " + worldData + " cases of COVID-19 today, globally"); /*!< Posts world COVID-19 case numbers*/

    postProvinces(); /* Post Testing Numbers for Canadian Provinces*/

    twit_deaths_recoveries.sendTweet("There were " + canadaDeaths + " COVID-19 deaths and " + canadaRecoveries + " COVID-19 recoveries today in Canada"); /*!< Posts Canada COVID-19 deaths and recoveries*/

    twit.sendTweet("Check out this article: "+ newsArticles); /*!< Posts relevent COVID-19 news article URL*/

}
