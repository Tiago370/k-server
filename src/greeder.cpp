#include<string>
#include<iostream>
#include<climits>
#include<fstream>
#include "greeder.h"
using namespace std;
Greeder::Greeder(string file_map, string file_requests, unsigned int idLote){
    readRequests(file_requests);
    environment = new Environment(file_map);
    this->idLote = idLote;
}
Greeder::~Greeder(){   }
void Greeder::printRequests(){
    cout << "Requests: ";
    for(unsigned int i = 0; i < nRequests; i++){
        cout << requests[i] << " ";
    }
    cout << endl;
}
void Greeder::solve(){
    environment->reset();
    for(unsigned int j = 0; j < nRequests; j++){
        unsigned int closest_server = environment->closest_server(requests[j]);
        environment->move(requests[j], closest_server);
    }
    cout << "Algoritmo Greedy" << endl;
    cout << "\tCusto acumulado: " << environment->getCustoAcumulado() << endl;
    //arquivo da tabela de resultados do algoritmo Greedy
    string arquivo = "dados/saida/lote" + to_string(this->idLote) + "/resultados-greedy.csv";
    ofstream file(arquivo.c_str(), std::ios_base::app | std::ios_base::out);
    file << idLote << ", " << environment->getCustoAcumulado() << endl;


}
unsigned int Greeder::closest_server(unsigned int node){
    unsigned int menor_distancia = INT_MAX;
    unsigned int server = 0;
    for(unsigned int i = 0; i < environment->getKServes(); i++){
        unsigned int distancia = environment->getCusto(environment->getKLocal()[i], node);
        if(distancia < menor_distancia){
            menor_distancia = distancia;
            server = i;
        }
    }
    return server;
}
void Greeder::readRequests(string file_requests){
    ifstream file(file_requests);
    if(!file.is_open()){
        cout << "Erro ao abrir arquivo" << endl;
        exit(1);
    }
    
    file >> nRequests;
    requests.resize(nRequests);
    for(unsigned int i = 0; i < nRequests; i++){
        file >> requests[i];
    }
    file.close();
}
