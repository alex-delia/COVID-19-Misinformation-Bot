#include <iostream>
using namespace std;

/**
 * newsArticles.h/newsArticles.cpp
 * 
 * @brief This class uses libcurl to get information from the NewsAPI 
 * @author Janki Chaudhari (251004226)
 * 
 * This class uses libcurl which fetches information from News API gets the latest news in canada corrosponding to the key word.
 * the function getNewsArticles returns the link to the top news article corrosponding to the hash tag in the tweet 
 */
class NewsArticles {
    public:
        static size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);
        static string getNewsArticles(string hashtag);
};