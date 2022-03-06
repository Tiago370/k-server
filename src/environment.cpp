#include "environment.h"
#include <fstream>
#include <iostream>
using namespace std;
Environment::Environment(string arquivo){
    ifstream file(arquivo);
    if(!file.is_open()){
        cout << "Erro ao abrir arquivo" << endl;
        exit(1);
    }
    cout << "Abrindo arquivo: " << arquivo << endl;
    file >> nNodes;
    file >> kServes;
    k_local_fixo.resize(kServes);
    for(unsigned int i = 0; i < kServes; i++){
        file >> k_local_fixo[i];
    }
    
    custo.resize(nNodes);
    for(unsigned int i = 0; i < nNodes; i++){
        custo[i].resize(nNodes);
    }
    
    for(unsigned int i = 0; i < nNodes; i++){
        for(unsigned int j = 0; j < nNodes; j++){
            double custo_aux;
            file >> custo_aux;
            custo[i][j] = custo_aux;
        }
    }

    file.close();
    custo_acumulado = 0;
    copy_k_local();
}
Environment::~Environment(){    
}
void Environment::print(){
    cout << "Nodes: " << nNodes << endl;
    cout << "Serves: " << kServes << endl;
    cout << "Custo: " << endl;
    for(unsigned int i = 0; i < nNodes; i++){
        for(unsigned int j = 0; j < nNodes; j++){
            cout << custo[i][j] << " ";
        }
        cout << endl;
    }
    cout << "K_local: ";
    for(unsigned int i = 0; i < kServes; i++){
        cout << k_local[i] << " ";
    }
    cout << endl;
    cout << "Custo acumulado: " << custo_acumulado << endl;
}
void Environment::move(unsigned int node, unsigned int server){
    unsigned int node_anterior = k_local[server];
    k_local[server] = node;
    custo_acumulado += custo[node_anterior][node];
}
unsigned int Environment::get_nNodes(){
    return nNodes;
}
void Environment::copy_k_local(){
    k_local.resize(kServes);
    for(unsigned int i = 0; i < kServes; i++){
        k_local[i] = k_local_fixo[i];
    }
}
void Environment::reset(){
    custo_acumulado = 0;
    copy_k_local();
}
unsigned int Environment::getCustoAcumulado(){
    return custo_acumulado;
}
vector<unsigned int> Environment::getKLocal(){
    return k_local;
}
unsigned int Environment::getCusto(unsigned int node1, unsigned int node2){
    return custo[node1][node2];
}
unsigned int Environment::closest_server(unsigned int node){
    unsigned int menor_custo = custo[k_local[0]][node];
    unsigned int closest_server = 0;
    for(unsigned int i = 1; i < kServes; i++){
        if(custo[k_local[i]][node] < menor_custo){
            menor_custo = custo[k_local[i]][node];
            closest_server = i;
        }
    }
    return closest_server;
}
unsigned int Environment::getKServes(){
    return kServes;
}
void Environment::printMapa(){
    cout << nNodes << " " << kServes << endl;
    for(unsigned int i = 0; i < kServes; i++){
        cout << k_local[i] << endl;
    }
    for(unsigned int i = 0; i < nNodes; i++){
        for(unsigned int j = 0; j < nNodes; j++){
            cout << custo[i][j] << " ";
        }
        cout << endl;
    }
}