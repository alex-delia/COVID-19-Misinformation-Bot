#include <iostream>
#include "json.hpp"
/** covid.h/covid.cpp
 * @brief this class communicates with multiple Covid-19 APIs to provide relevant methods
 * @author Alex D'Elia (251021780)
 * @author Huda Mukhtar (251030469)
 * 
 * This class uses the Covid-19 apis to retrieve data and implement the important Covid functions. Each of these functions
 *  are responsible for retrieving and parsing json data from the Covid APIs. These functions are used in the main class to
 * fetch data for tweets 
 */

using namespace std;

class covid {
    public:
        static size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);
        static string getWorldData();
        static nlohmann::json getCanadaData();
        static string getTests(string province);
        static string getCanadaDeaths();
        static string getCanadaRecoveries();
        static int getDailyTotalRecovs();
        static int getLastWeekRecovs();
};