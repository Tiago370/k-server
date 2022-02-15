#include <vector>
#include <string>
#include "environment.h"
#include "net.h"
using namespace std;
class Trainer {
    public:
        Trainer(string mapa, string requests);
        ~Trainer();
        void printRequests();
        void randomMutation(unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nPopulation, unsigned int nGenerations);
        void random();
    private:
        Environment *environment;
        unsigned int nRequests;
        vector<unsigned int> requests;
        Net champion;
        void readRequests(string requests);
   };