#include <iostream>
#include "include/curl/curl.h"
#include "twitter.h"
#include "covid.h"

using namespace std;

int main(){
    Twitter weeklyRecovsTweet = Twitter();

    int totalRecovs = covid::getDailyTotalRecovs();
    int lastWeekRecovs = covid::getLastWeekRecovs();

    int recovsThisWeek =  totalRecovs - lastWeekRecovs;

    weeklyRecovsTweet.sendTweet("There were " + recovsThisWeek + " COVID-19 recoveries in Canada this week");

}