#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <climits>
#include "trainer.h"
#include "net.h"
using namespace std;
Trainer::Trainer(string file_mapa, string file_requests){
    readRequests(file_requests);
    environment = new Environment(file_mapa);
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
	for(int i = 0; i < nPopulation; i++){
		populacao.push_back(Net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs));
	}
	int generation_number = 0;
    long long fitness = LONG_LONG_MAX;
    int nElite = nPopulation*0.05;
	//Criterio de parada
    unsigned int stop = 0;
    clock_t end,start;
    start = clock();
	while(generation_number < nGenerations && stop < 200){
        //cerr << "aqui começo" << endl;
		//Para cada individuo da populacao
		for(int i = 0; i < nPopulation; i++){
			if(i >= nElite) populacao[i].mutation();
            populacao[i].setFitness(0);
            //Para cada caso de teste
            for(int j = 0; j < nTrainingSet; j++){
                unsigned int ignorado;
                play(&populacao[i]);
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
		for(int i = nElite; i < (int)nPopulation*rDesc; i++){
            populacao[i].copiar_rede(&(populacao[i%nElite]));
		}
		for(int i = (int)nPopulation*rDesc; i < nPopulation; i++){
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
    end = clock();
    std::ofstream outfile;
    outfile.open("dados-treinamento-redes.csv", std::ios_base::app); // append instead of overwrite
    if(escalonamentos->at(0).getOrder()) outfile << "O";
    if(escalonamentos->at(0).getRelativize()) outfile << "R";
    if(escalonamentos->at(0).getSubtract()) outfile << "S";
    outfile << ",";
    outfile << nHiddenLayers;
    outfile << "x";
    outfile << nHiddenNeurons;
    outfile << ",";
    outfile << generation_number;
    outfile << ",";
    outfile << (double)(end-start)/(double)(CLOCKS_PER_SEC);
    outfile << endl;
    //outfile << "Configuraçao,Tamanho,nGerações,Tempo de Treinamento" << endl;
    outfile.close();
    cout << "Fitness do campeão " << champion.getFitness() << endl;
    //play(&champion, &(escalonamentos->at(0)), 13, 11, true);
    //play(&champion, &(escalonamentos->at(1)), 13, 11, true);
    //play(&champion, &(escalonamentos->at(2)), 13, 11, true);
    //play(&champion, &(escalonamentos->at(3)), nInputs, 10, true);
    //play(&champion, &(escalonamentos->at(4)), 13, 11, true);
    champion.saveNet(net_file);

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