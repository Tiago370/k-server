#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <string>

using namespace std;

string vectorToString(vector<int>* v);
string doubleVectorToString(vector<double>* v);
void transferList(vector <int>* origem, vector <int>* destino);

int retira(vector<unsigned int> &v, unsigned int i);
void insereNoComeco(vector<unsigned int> &v, int value);
void empacota(vector<unsigned int> &v, int pos, int value);
void print(vector<unsigned int>* v);
void stringToChar(string s, char* c);
#endif