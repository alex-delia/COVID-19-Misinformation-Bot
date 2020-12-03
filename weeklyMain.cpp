#include <iostream>
#include "include/curl/curl.h"
#include "twitter.h"
#include "covid.h"

using namespace std;
/** Main method that will only run once a week
 * 
 * This main method is created separately in order to run the covid functions that are only required to be run once a week
 * This is scheduled on the Raspberry Pi to ensure consistency
 */
int main(){
    Twitter weeklyRecovsTweet = Twitter();

    int totalRecovs = covid::getDailyTotalRecovs();
    int lastWeekRecovs = covid::getLastWeekRecovs();

    int recovsThisWeek =  totalRecovs - lastWeekRecovs;

    weeklyRecovsTweet.sendTweet("There were " + recovsThisWeek + " COVID-19 recoveries in Canada this week");

}