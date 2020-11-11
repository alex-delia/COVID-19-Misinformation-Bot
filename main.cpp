#include <iostream>
#include "include/curl/curl.h"
#include "twitter.h"
#include "covid.h"
using namespace std;
int main()
{
    Twitter twit = Twitter();

    string worldData = Covid::getWorldData();

    twit.sendTweet("There were " + worldData + " cases of COVID-19 today, globally");
}