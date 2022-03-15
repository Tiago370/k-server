#include <string>
#include "trainer.h"
#include "greeder.h"
#include <iostream>
int main(int argc, char *argv[]){
    if  (argc == 1) {
        cout << "Faltam argumentos" << endl;
        return 1;
    }
    string algoritmo = argv[1];
    if(algoritmo == "-greedy"){
        string idLote = argv[4];
        Greeder *greeder = new Greeder(argv[2], argv[3], atoi(idLote.c_str()) );
        greeder->solve();
        delete greeder;
    }
    else if(algoritmo == "-random"){
        Trainer *trainer = new Trainer(argv[2], argv[3]);
        trainer->random();
        delete trainer;
    }
    else if(algoritmo == "-training"){
        unsigned int nGenerations = atoi(argv[2]);
        unsigned int nIndividuals = atoi(argv[3]);
        unsigned int nHiddenLayers = atoi(argv[4]);
        unsigned int nHiddenNeurons = atoi(argv[5]);
        unsigned int generationsWithoutImprovement = atoi(argv[6]);
        unsigned int loteId = atoi(argv[7]);
        unsigned int nInstances = atoi(argv[8]);
        unsigned int nServers = atoi(argv[9]);
        Trainer trainer = Trainer();
        trainer.randomMutation(nHiddenLayers, nHiddenNeurons, nIndividuals, nGenerations, generationsWithoutImprovement, loteId, nInstances, nServers);  
        cout << "ok" << endl;
    }else if(algoritmo == "-run"){
        Trainer trainer = Trainer(string(argv[2]), string(argv[3]));
        trainer.setNet(argv[4]);
        string loteId = argv[5];
        trainer.run(atoi(loteId.c_str()));
        }else{
        cout << "Algoritmo inválido" << endl;
        return 1;
    }
    return 0;
}

//./build/k-server -training <nGenerations> <nIndividuals> <nHiddenLayers> <nHiddenNeurons> <generationsWithoutImprovement> <loteId> <nInstances>
