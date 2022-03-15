#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <climits>
#include <algorithm>
#include <ios>
#include <fstream>
#include "trainer.h"
#include "net.h"
#include "environment.h"
using namespace std;
Trainer::Trainer(){
    this->environment = NULL;
    this->nRequests = 0;
    this->champion = Net();
    this->lastResult = 0;
}
Trainer::Trainer(string mapa, string reqs){
    environment = new Environment(mapa);
    readRequests(reqs);
    nRequests = this->requests[0].size();
}
Trainer::~Trainer(){ }
void Trainer::printRequests(){ }
void Trainer::randomMutation(unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nPopulation, unsigned int nGenerations, unsigned int generationsWithoutImprovement, unsigned int loteId, unsigned int nInstances, unsigned int nServers){
    readInstances(loteId, nInstances);
    cout << "nHiddenLayers: " << nHiddenLayers << " nHiddenNeurons: " << nHiddenNeurons << endl;
    unsigned int nInputs = nServers;
    unsigned int nOutputs = nServers;
    champion = Net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs);
    champion.setFitness(__DBL_MAX__);
	vector<Net> populacao;
    //Criando a população inicial
	for(unsigned int i = 0; i < nPopulation; i++){
		populacao.push_back(Net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs));
	}
    //treinando a população
	unsigned int generation_number = 0;
    long double fitness = LONG_LONG_MAX;
    unsigned int nElite = nPopulation*0.05;
    unsigned int stop = 0;

	while(generation_number < nGenerations && stop < generationsWithoutImprovement){
        //ordenando a população
		
		for(unsigned int i = 0; i < nPopulation; i++){
            //Mutação
			if(i >= nElite) populacao[i].mutation();
            //populacao[i].setFitness(0);
            //Cada individuo da populacao resolve todas as instancias
            // Zerando o fitness
            populacao[i].setFitness(0);
            for(unsigned int j = 0; j < requests.size(); j++){
                play(&populacao[i], j+1);
            }
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
    string rede_path = "dados/saida/lote" + to_string(loteId) + "/rede.txt";
    cout << rede_path << endl;
    champion.saveNet((char*)rede_path.c_str());
}
void Trainer::readRequests(string file_requests){
    vector<unsigned int> instance;
    ifstream file(file_requests.c_str());
    // ler o número de requisições
    unsigned int nReq;
    file >> nReq;
    // ler as requisições
    for(unsigned int i = 0; i < nReq; i++){
        unsigned int req;
        file >> req;
        instance.push_back(req);
    }
    requests.push_back(instance);
}
void Trainer::random(){
    cout << "Algoritmo Random" << endl;
    cout << "Buscando..." << endl;
}
void Trainer::play(Net* net, unsigned int instanceId){
    if(instanceId != 0){
        vector<unsigned int> requisicoes = requests[instanceId-1];
        environment->reset();
        for(unsigned int j = 0; j < nRequests; j++){
            //Obtendo os servidores
            vector<unsigned int> local_do_server = environment->getKLocal();
            //Para cada servidor, obtendo o custo
            vector<double> inputs(environment->getKServes());
            vector<double> outputs(environment->getKServes());
            for(unsigned int i = 0; i < inputs.size(); i++){
                inputs[i] = environment->getCusto(local_do_server[i], requisicoes[j]);
            }
            //Ativando a rede
            net->activateLayers(&inputs, &outputs);
            //Escolhendo o servidor
            bool found = false;
            for(unsigned int i = 0; i < outputs.size(); i++){
                if(outputs[i] > 0){
                    environment->move(requisicoes[j], i);
                    //cout << "moveu " << requisicoes[j] << " para " << i << endl;
                    found = true;
                    break;
                }
            }
            if(!found){
                environment->move(requisicoes[j], 0);    
            }
            
        }
        //Atualizando o fitness
        double custo_total = environment->getCustoAcumulado();
        if(custo_total > 0.00001){
            double fitness_da_rede = net->getFitness();
            net->setFitness(fitness_da_rede + custo_total);
        }else{
            net->setFitness(__DBL_MAX__);        
        }
        lastResult = custo_total;
    }
}
void Trainer::run(unsigned int idLote){
    cout << "Rodando com a rede treinada..." << endl;
    lastResult = 0;
    play(&champion, 1);
    cout << "Custo acumulado: " << champion.getFitness() << endl;
    //arquivo da tabela de resultados da rede
    string arquivo = "dados/saida/lote" + to_string(idLote) + "/resultados-rede.csv";
    ofstream file(arquivo.c_str(), std::ios_base::app | std::ios_base::out);
    file << idLote << ", " << champion.getFitness() << endl;


}
void Trainer::setNet(char* file_net){
    cout << "Carregando rede..." << endl;
    champion.openNet(file_net);
    cout << "Rede carregada com sucesso" << endl;

}
bool squareCompareByFitness(Net &a, Net &b){
    return a.getFitness() < b.getFitness();
}
void Trainer::readInstances(unsigned int loteId, unsigned int nInstances){
    cout << "Lendo o mapa..." << endl;
    string file_map = "dados/instancias/lote" + to_string(loteId) + "/mapa.txt";
    cout << "Arquivo: " << file_map << endl;

    environment = new Environment(file_map);
    cout << "Mapa carregado com sucesso" << endl;
    //lendo as requisicoes
    cout << "Lendo as requisicoes..." << endl;

    for(unsigned int i = 0; i < nInstances; i++){
        string file_requests = "dados/instancias/lote" + to_string(loteId) + "/req-trn/req" + to_string(i+1) + ".txt";
        readRequests(file_requests);
        cout << "Lendo a instancia " << (i+1) << endl;
    }
    nRequests = requests[0].size();
}