#include <iostream>
#include "twitter.h"
using namespace std;
int main()
{
    Twitter twit = Twitter();
    twit.sendTweet("Hello, World!");
}