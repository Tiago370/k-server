#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <climits>
#include <algorithm>
#include "trainer.h"
#include "net.h"
#include "environment.h"
using namespace std;
Trainer::Trainer(string mapa, string requests){
    environment = new Environment(mapa);
    readRequests(requests);
}
Trainer::~Trainer(){   }
void Trainer::printRequests(){
    cout << "Requests: ";
    for(unsigned int i = 0; i < nRequests; i++){
        cout << requests[i] << " ";
    }
    cout << endl;
}
void Trainer::randomMutation(unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nPopulation, unsigned int nGenerations){
    cout << "nHiddenLayers: " << nHiddenLayers << " nHiddenNeurons: " << nHiddenNeurons << endl;
    unsigned int nInputs = environment->getKServes();
    unsigned int nOutputs = environment->getKServes();
    champion = Net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs);
    champion.setFitness(__DBL_MAX__);
	vector<Net> populacao;
    //Criando a população inicial
	for(unsigned int i = 0; i < nPopulation; i++){
		populacao.push_back(Net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs));
	}
    //treinando a população
	unsigned int generation_number = 0;
    long long fitness = LONG_LONG_MAX;
    unsigned int nElite = nPopulation*0.05;
    unsigned int stop = 0;
	while(generation_number < nGenerations && stop < 200){
		
		for(unsigned int i = 0; i < nPopulation; i++){
            //Mutação
			if(i >= nElite) populacao[i].mutation();
            //populacao[i].setFitness(0);

            //Resolve o problema para cada individuo da populacao
            play(&populacao[i]);

            if(populacao[i].getFitness() < fitness){
                champion.copiar_rede(&populacao[i]);
                champion.setFitness(populacao[i].getFitness());
                fitness = populacao[i].getFitness();
                cout << "Melhor Fitness: " << fitness << endl;
                stop = 0;
            }

        }
		//Tentativa 1: os piores individuos serao refeitos, isso introduz aleatoriedade
		sort(populacao.begin(), populacao.end(), squareCompareByFitness);
        for(unsigned int i = 0 ; i < populacao.size(); i++){
            //cout << i << ": "<< populacao[i].getFitness() << endl;
        }
        
        double rDesc = (double)generation_number/nGenerations;
        if(rDesc < 0.1) rDesc = 0.1;
        if(rDesc > 0.9) rDesc = 0.9;
        cout << "Relite: " << rDesc << endl;
		//exit(1);
        for(int i = nElite; i < (int)nPopulation*rDesc; i++){
            populacao[i].copiar_rede(&(populacao[i%nElite]));
		}
        //exit(1);    
		for(unsigned int i = (unsigned int)nPopulation*rDesc; i < nPopulation; i++){
			populacao[i].rerandom();
		}
		//Tentativa 2: a cada 100 geracoes eu coloco o campeao de volta na populacao
		if(generation_number%1 == 0){
			//campeao se reproduz
			//populacao[nPopulation-1].copiar_rede(&champion);
		}
		generation_number++;
        stop++;
        //cerr << "aqui fim" << endl;
	}
    champion.saveNet((char*)"rede.txt");
    
}
void Trainer::readRequests(string file_requests){
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
void Trainer::random(){
    cout << "Algoritmo Random" << endl;
    cout << "Buscando..." << endl;
    unsigned int menor_custo_acumulado = INT_MAX;
    vector<unsigned int> melhor_k_local;
    for(unsigned int i = 0; i < 10000000; i++){
        environment->reset();
        for(unsigned int j = 0; j < nRequests; j++){
            unsigned int server = rand() % 2;
            environment->move(requests[j], server);
        }
        if(environment->getCustoAcumulado() < menor_custo_acumulado){
            menor_custo_acumulado = environment->getCustoAcumulado();
            melhor_k_local = environment->getKLocal();
            cout << "\tCusto acumulado: " << environment->getCustoAcumulado() << endl;
        }
    }
}
void Trainer::play(Net* net){
    environment->reset();
    for(unsigned int j = 0; j < nRequests; j++){
        //Obtendo os servidores
        vector<unsigned int> local_do_server = environment->getKLocal();
        //Para cada servidor, obtendo o custo
        vector<double> inputs(environment->getKServes());
        vector<double> outputs(environment->getKServes());
        for(unsigned int i = 0; i < inputs.size(); i++){
            inputs[i] = environment->getCusto(local_do_server[i], requests[j]);
        }
        //Ativando a rede
        net->activateLayers(&inputs, &outputs);
        //Escolhendo o servidor
        bool found = false;
        for(unsigned int i = 0; i < outputs.size(); i++){
            if(outputs[i] > 0){
                environment->move(requests[j], i);
                found = true;
                break;
            }
        }
        if(!found){
            environment->move(requests[j], 0);    
        }
        //Atualizando o fitness
        double custo_total = environment->getCustoAcumulado();
        if(custo_total > 0.00001){
            net->setFitness(custo_total);
        }else{
            net->setFitness(__DBL_MAX__);        
        }
        lastResult = custo_total;
    }
}
void Trainer::run(){
    cout << "Rodando com a rede treinada..." << endl;
    play(&champion);
    cout << "Custo acumulado: " << lastResult << endl;
}
void Trainer::setNet(char* file_net){
    cout << "Carregando rede..." << endl;
    champion.openNet(file_net);
    cout << "Rede carregada com sucesso" << endl;

}
bool squareCompareByFitness(Net &a, Net &b){
    return a.getFitness() < b.getFitness();
}