#ifndef TRAINER_H
#define TRAINER_H
#include <vector>
#include <string>
#include "environment.h"
#include "net.h"
using namespace std;
class Trainer {
    public:
        Trainer(string mapa, string reqs);
        Trainer();
        ~Trainer();
        void printRequests();
        void randomMutation(unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nPopulation, unsigned int nGenerations, unsigned int generationsWithoutImprovement, unsigned int loteId, unsigned int nInstances, unsigned int nServers);
        void random();
        void run(unsigned int idLote);
        void setNet(char* file_net);
    private:
        Environment *environment;
        vector<vector<unsigned int>> requests;
        unsigned int nRequests;
        Net champion;
        void readRequests(string requests);
        void readInstances(unsigned int loteId, unsigned int nInstances);
        void play(Net *net, unsigned int instanceId);
        unsigned int lastResult;
   };
bool squareCompareByFitness(Net &a, Net &b);
#endif