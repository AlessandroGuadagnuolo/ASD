#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <direct.h>
using namespace std;
const int INFINITY = 9999;

enum colore { WHITE, GREY, BLACK};

class nodo{
    public:
        int colore = WHITE; 
        int parent;
        int distanza; //per la BFS, così posso anche ottenere la distanza 
                      //di ogni nodo dal nodo di partenza (in termini di numero di archi)
        int t_scoperta;
        int t_complet;
        vector<int> adiacenti;
};

class grafo{
    public:
        vector<nodo> nodi;
        int V;  //numero di vertici che leggerò dal file nella prima riga
        grafo(int vertici) : V(vertici) { nodi.resize(V); }
        void add_edge(int u, int v);
        void BFS(int s,std::ofstream& outputFile);
        void DFS(std::ofstream& outputFile);
        void DFS_visit(int u, int& time,std::ofstream& outputFile);
};


void grafo::DFS(std::ofstream& outputFile){
    cout<<"DFS avviata..."<<endl;
    for (int i=0; i < this-> V; i++){
        this->nodi[i].colore = WHITE;
        this->nodi[i].parent = -1;
    }
    int time = 0;
    for(int i=0; i < this-> V; i++){
        if(this->nodi[i].colore == WHITE){
            DFS_visit(i, time, outputFile);
        }
    }
}

void grafo::DFS_visit(int u, int& time, std::ofstream& outputFile){
    this->nodi[u].colore = GREY;
    time ++;
    this->nodi[u].t_scoperta = time;
    for(auto v: this->nodi[u].adiacenti){
        if(this->nodi[v].colore == WHITE){
            this->nodi[v].parent = u;
            DFS_visit(v,time, outputFile);
        }
    }
    this->nodi[u].colore = BLACK;
    time++;
    this->nodi[u].t_complet = time;
    outputFile << "Nodo " << u <<"|Colore "<<this->nodi[u].colore << "|Tempo di scoperta " << this->nodi[u].t_scoperta << "|Tempo di completamento " <<this->nodi[u].t_complet << "|Parent " << this->nodi[u].parent << endl;
}

void grafo::BFS(int s, std::ofstream& outputFile){
    cout<<"BFS avviata..."<<endl;
    for (int i=0; i < this-> V; i++){
        if(i!=s){
            this->nodi[i].colore = WHITE;
            this->nodi[i].parent = -1;
            this->nodi[i].distanza = INFINITY;
        }
    }
    this->nodi[s].colore = GREY;
    this->nodi[s].parent = -1;
    this->nodi[s].distanza = 0;
    queue<int> coda;
    coda.push(s);
    while (!coda.empty()){
        int u = coda.front();
        coda.pop();
        for(auto v:this->nodi[u].adiacenti){
            if(this->nodi[v].colore == WHITE){
                this->nodi[v].colore = GREY;
                this->nodi[v].distanza = this->nodi[u].distanza + 1;
                this->nodi[v].parent = u;
                coda.push(v);
            }
        }
        this->nodi[u].colore = BLACK;
        outputFile <<"Nodo " << u << "|Distanza " << this->nodi[u].distanza << "|Parent " << this->nodi[u].parent << endl;
    }
}

void grafo::add_edge(int u, int v){
    this->nodi[u].adiacenti.push_back(v);
}


int main(){
    int V=0, E=0, src, dst, w;
    string path = "../input.txt";
    ifstream inputFile(path);
    inputFile >> V >> E;
    cout<<"V "<<V << " E "<< E<<endl;
    grafo G(V);
    for(int i=0; i < E; i++){
        inputFile >> src >> dst >> w;
        G.add_edge(src,dst);
    }
    ofstream outputFile("output.txt");
    
    int s = 1;
    
    G.BFS(s, outputFile);
    
    ofstream outputFile2("output2.txt");

    G.DFS(outputFile2);
    inputFile.close();
    outputFile.close();
    outputFile2.close();
    return 0;
}