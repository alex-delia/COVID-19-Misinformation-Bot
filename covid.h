#include <iostream>
#include "json.hpp"

using namespace std;

class covid {
    public:
        static size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);
        static string getWorldData();
        static nlohmann::json getCanadaData();
        static string getCanadaTests();
        static string getCanadaDeaths();
        static string getCanadaRecoveries();

};