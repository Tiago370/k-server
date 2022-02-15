#pragma once
#include <vector>
#include <string>
using namespace std;

class Environment{
public:

	Environment(string arquivo);
	~Environment();

	void move(unsigned int node, unsigned int server);
	void print();
	unsigned int get_nNodes();
	void reset();
	vector<unsigned int> getKLocal();
	unsigned int getCustoAcumulado();
	unsigned getCusto(unsigned int node1, unsigned int node2);
	unsigned int closest_server(unsigned int node);
	unsigned int getKServes();
private:
	unsigned int nNodes;
	unsigned int kServes;
    unsigned int custo_acumulado;
	vector<vector<unsigned int>> custo;
    vector<unsigned int> k_local_fixo;
	vector<unsigned int> k_local;
	vector<unsigned int> historico;
	void copy_k_local();
};
