#include <string>
#include "trainer.h"
#include "greeder.h"
#include <iostream>
int main(int argc, char *argv[]){
    if(argc < 4){
        cout << "Uso: " << argv[0] << " <mapa> <requests> <algoritmo>" << endl;
        return 1;
    }
    string mapa = argv[1];
    string requests = argv[2];
    string algoritmo = argv[3];
    //string net_file = argv[4];
    Trainer trainer(mapa, requests);
    Greeder greeder(mapa, requests);
    if(algoritmo == "greedy"){
        greeder.solve();
    }
    else if(algoritmo == "random"){
        trainer.random();
    }
    else if(algoritmo == "training"){
        trainer.randomMutation(2, 2, 100, 10000);
        cout << "ok" << endl;
    }else if(algoritmo == "run"){
        trainer.setNet((char*)"rede.txt");
        trainer.run(); 
        }else{
        cout << "Algoritmo inválido" << endl;
        return 1;
    }
    return 0;
}
// Para compilar sem alteração nos códigos .h: make
// Para compilar com alteração nos códigos .h: make clean && make
// Para rodar o trainamento: ./build/k-server <mapa> <requests> training
// Para rodar o greedy: ./build/k-server <mapa> <requests> greedy

//./build/k-server  intancias/mapa_1.txt  intancias/requests_1.txt training
//./build/k-server  instancias/mapa_1.txt  instancias/requestsTeste_1.txt run rede.txt