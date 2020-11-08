#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "twitter.h"
#include "twitterClient.h"
using namespace std;

void Twitter::sendTweet(string input)
{
    twitCurl twit;
    string resp;
    twit.getOAuth().setConsumerKey("ulNuJWQiUBVUn9XV2SawRQwDg");
    twit.getOAuth().setConsumerSecret("ArkIXUoHL9CiGZV9AsbZFbiWc4TMMEUFwd91tlVFMRhhJaiV1h");
    twit.getOAuth().setOAuthTokenKey("1324153496338354179-1hlRx3AkUwCRB2ptynR3dqYQgA5Usb");
    twit.getOAuth().setOAuthTokenSecret("os0Y2gCaoigZD0x6Q1w6HQHbPXhQE9qqQqtPJnxqq5VwJ");

    //Send API Call
    if(twit.statusUpdate(input)){
        twit.getLastWebResponse(resp);
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", resp.c_str() );
    }
    else
    {
        twit.getLastCurlError( resp );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", resp.c_str() );
    }

}