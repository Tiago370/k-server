#include <string>
#include "trainer.h"
#include "greeder.h"
#include <iostream>
int main(int argc, char *argv[]){
    if(argc != 4){
        cout << "Uso: " << argv[0] << " <mapa> <requests> <algoritmo>" << endl;
        return 1;
    }
    string mapa = argv[1];
    string requests = argv[2];
    string algoritmo = argv[3];
    Trainer trainer(mapa, requests);
    Greeder greeder(mapa, requests);
    if(algoritmo == "greedy"){
        greeder.solve();
    }
    else if(algoritmo == "random"){
        trainer.random();
    }
    else if(algoritmo == "training"){
        trainer.randomMutation(2, 2, 100, 1000000);
        cout << "ok" << endl;
    }
    else{
        cout << "Algoritmo inválido" << endl;
        return 1;
    }
    return 0;
}