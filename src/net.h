#ifndef NET_H
#define NET_H
#include "neuron.h"
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class Net{
public:
	int nInputs;
	int nHiddenLayers;
	int nHiddenNeurons;
	int nOutput;
	double fitness;

	vector<vector<Neuron>> layers;

	Net(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutput);
	Net();

	~Net();

	void setFitness(double pfitness);
	double getFitness();
	int getNInputs();
	int getNHiddenLayers();
	int getNHiddenNeurons();
	int getNOutput();

	void mutation();

	//activerLayers recebe um vetor de entrada, ativa todas as camadas e
	//devolve o resultado no vetor poutputs, que deve ser passado previamente alocado
	void activateLayers(vector<double>* inputs, vector<double>* poutputs);
	void copiar_rede(Net * origem);
	void imprimeRede();
	void rerandom();
	void openNet(char* arquiv);
	void saveNet(char* arquiv);

private:
	vector<vector<Neuron>>* getLayers();
	void imprimeCamada(unsigned int i);
};
#endif