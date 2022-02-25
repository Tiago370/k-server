#ifndef TRAINER_H
#define TRAINER_H
#include <vector>
#include <string>
#include "environment.h"
#include "net.h"
using namespace std;
class Trainer {
    public:
        Trainer(string file_map, string file_requests);
        ~Trainer();
        void printRequests();
        void randomMutation(unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nPopulation, unsigned int nGenerations);
        void random();
        void run();
        void setNet(char* file_net);
    private:
        Environment *environment;
        unsigned int nRequests;
        vector<unsigned int> requests;
        Net champion;
        void readRequests(string requests);
        void play(Net *net);
        unsigned int lastResult;
   };
bool squareCompareByFitness(Net &a, Net &b);
#endif