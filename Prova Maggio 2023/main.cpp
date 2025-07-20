#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

struct Arco{
    int d;
    int p;
    Arco(int d, int p): d(d), p(p){}
};

class Grafo{
public:
    int nodi, archi;
    vector<vector<Arco>> adjList;
    Grafo(): nodi(0), archi(0){}
    //per PRIM, in modo da non dover passare i dati, e permettere a PRINT_MST di leggerli e stamparli
    vector<int> key;
    vector<int> predecessore;
    vector<bool> MST;
    void BFS(int s);
    void PRIM(int r);
    void PRINT_MST();
    bool IS_BINARY();
};

void Grafo::BFS(int s){
    vector<int> distanza(nodi+1,-1);
    vector<int> predecessore(nodi+1,-1);
    queue<int> q;
    distanza[s]=0;
    q.push(s);

    while (!q.empty()){
        int u = q.front();
        q.pop();
        for(const Arco& arco: adjList[u]){
            int v = arco.d;
            if(distanza[v]==-1){
                distanza[v]= distanza[u]+1;
                predecessore[v]=u;
                q.push(v);
            }
        }
    }
    ofstream output("output.txt");
    if(!output.is_open()){
        cout<<"Errore apertura file di output"<<endl;
        return;
    }

    for(int i=1; i<=nodi; i++){
        output<<i<<"\t"<<distanza[i]<<"\t";
        if(predecessore[i]==-1){
            output<<"NIL";
        }
        else{
            output<<predecessore[i];
        }
        output<<endl;
    }
    output.close();
    cout<<"BFS completata"<<endl;
}

void Grafo::PRIM(int r){
    key.resize(nodi+1);
    predecessore.resize(nodi+1);
    MST.resize(nodi+1);

    for (int i = 0; i <= nodi; ++i) {
        key[i] = 9999;
        predecessore[i] = -1;
        MST[i] = false;
    }
    key[r]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<>> pq;
    pq.push({0,r});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if(MST[u]) continue; //ovvero salta tutto fino alla fine del ciclo
        MST[u]= true;
        for(const Arco& arco: adjList[u]){
            int v = arco.d;
            int peso = arco.p;
            if(!MST[v] && peso < key[v]){
                key[v] = peso;
                predecessore[v] = u;
                pq.push({key[v],v});
            }
        }
    }
}

void Grafo::PRINT_MST(){
    for (int v = 1; v <= nodi; ++v) {
        if (predecessore[v] != -1) {
            cout << predecessore[v] << " - " << v << "\n";
        }
    }
}

bool Grafo::IS_BINARY(){
    vector<int> figli(nodi+1,0);
    for(int v=1;v<=nodi;v++){
        int p = predecessore[v];
        if(p != -1){
            figli[p]++;
            if(figli[p]> 2) return false;
        }
    }
    return true;
}

int main()
{
    ifstream input("input.txt");
    if (!input.is_open()){
        cout<<"Errore apertura file di input"<<endl;
        return 1;
    }
    Grafo grafo;
    input >> grafo.nodi >> grafo.archi;

    grafo.adjList.resize(grafo.nodi+1);
    for(int i=0; i<grafo.archi; i++){
        int src, dst, peso;
        input >> src >> dst >> peso;
        grafo.adjList[src].push_back(Arco(dst,peso));
        grafo.adjList[dst].push_back(Arco(src,peso));
    }
    input.close();
    cout<<"Grafo caricato"<<endl;

    grafo.BFS(1);
    grafo.PRIM(1);
    grafo.PRINT_MST();
    bool res=grafo.IS_BINARY();
    cout<<res;
    return 0;
}
