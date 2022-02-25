#include "util.h"
#include <iostream>
#include <cstring>
string vectorToString(vector<int>* v){
    string out = "[";
    for(unsigned int i = 0; i < v->size(); i++){
        std::string str_vi = std::to_string(v->at(i));
        out += str_vi + ", ";
    }
    return out + "]";
}
string doubleVectorToString(vector<double>* v){
    string out = "[";
    for(unsigned int i = 0; i < v->size(); i++){
        std::string str_vi = std::to_string(v->at(i));
        out += str_vi + ", ";
    }
    return out + "]";
}
void transferList(vector <int>* origem, vector <int>* destino){
    for(unsigned int i = 0; i < origem->size(); i++){
        int a = origem->at(i);
        destino->push_back(a);
    }
}
void print(vector<unsigned int>* v){
    for(unsigned int i = 0; i < v->size(); i++){
        cout << v->at(i) << " ";
    }
    cout << endl;
}
int retira(vector<unsigned int> &v, unsigned int i){
    int j = v[i];
    for(unsigned int k = i; k < v.size()-1; k++) v[k] = v[k+1];
    v.resize(v.size()-1);
    return j;
}
void insereNoComeco(vector<unsigned int> &v, int value){
    v.resize(v.size()+1);
    for(unsigned int k = v.size()-1; k > 0; k--) v[k] = v[k-1];
    v[0] = value;
}
void empacota(vector<unsigned int> &v, int pos, int value){
    v[pos] += value;
    int a = retira(v, pos);
    insereNoComeco(v, a);
    for(unsigned int i = 0; i < v.size()-1; i++){
        if(v[i] > v[i+1]) break;
        int aux = v[i];
        v[i] = v[i+1];
        v[i+1] = aux;
    }
}
void stringToChar(string s, char* c){
    c = new char[s.length()+1];
    strcpy(c, s.c_str());
}