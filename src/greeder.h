#ifndef GREEDER_H
#define GREEDER_H
#include<vector>
#include<string>
#include "environment.h"
class Greeder {
    public:

        Greeder(string file_map, string file_requests);
        ~Greeder();
        void printRequests();
        void readRequests(string file_requests);
        void solve();
    private:
        unsigned int nRequests;
        vector<unsigned int> requests;
        Environment *environment;
        unsigned int closest_server(unsigned int node);
};
#endif