#include <iostream>
using namespace std;

class Covid {
    public:
        static size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);
        static string getWorldData();
};