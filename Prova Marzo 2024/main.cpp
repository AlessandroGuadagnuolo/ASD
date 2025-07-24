#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

struct Arco{
    int d, p;
    Arco(int d, int p): d(d),p(p) {}
};

class Grafo{
public:
    int nodi, archi;
    vector<vector<Arco>> adjList;
    void TP_DFS();
    void DFS_visit(int u, stack<int>& L,vector<int>& colore,vector<int>& pred);
    vector<int> Bellman_ford(int S, int D);
    void Trova_cicli();
    void DFS_cicli(int u, vector<int>& colore, vector<int>& stackric, vector<int>& cammino);
};

void Grafo::TP_DFS(){
    vector<int> colore(nodi+1,0);
    vector<int> pred(nodi+1,-1);
    stack<int> L;
    for (int u=1; u<= nodi; u++){
        if(colore[u]== 0){
            DFS_visit(u,L,colore,pred);
        }
    }

    ofstream output("OUT.txt");
    vector<int> res;

    while(!L.empty()){
        res.push_back(L.top());
        L.pop();
    }

    for(int i=0;i<res.size();i++){
        output << res[i];
        if(i < res.size()-1)
            output << " ";
    }
    output << endl;
    output.close();
    cout<<"Ordinamento topologico completato"<<endl;
}

void Grafo::DFS_visit(int u, stack<int>& L,vector<int>& colore, vector<int>& pred){
    colore[u]= 1;
    for(const Arco& arco: adjList[u]){
        int v = arco.d;
        if (colore[v] == 0){
            DFS_visit(v,L,colore,pred);
        }
    }
    colore[u]=2;
    L.push(u);
}

vector<int> Grafo::Bellman_ford(int S, int D){
    vector<int> distanza(nodi+1,INT_MAX);
    vector<int> pred(nodi+1,-1);
    distanza[S]=0;

    for(int i=1;i<=nodi-1;i++){
        for(int u=1;u<=nodi;u++){
            if(distanza[u] != INT_MAX){
                for(const Arco& arco: adjList[u]){
                    int v = arco.d;
                    int peso = arco.p;

                    if(distanza[u] + peso < distanza[v]){
                        distanza[v] = distanza[u] + peso;
                        pred[v] = u;
                    }
                }
            }
        }
    }

    if(distanza[D]== INT_MAX){
        cout<<"nodo D non raggiungibile da S"<<endl;
    }
    vector<int> cammino;
    int corrente = D;
    while(corrente != -1){
        cammino.push_back(corrente);
        corrente = pred[corrente];
    }

    reverse(cammino.begin(),cammino.end());

    return cammino;
}

void Grafo::Trova_cicli(){
    vector<int> colore(nodi+1,0);
    vector<int> stackric(nodi+1,0);
    vector<int> cammino;

    cout<<"Cicli: "<<endl;
    for(int u=1;u<=nodi;u++){
        if(colore[u]== 0){
            DFS_cicli(u,colore,stackric,cammino);
        }
    }
}

void Grafo::DFS_cicli(int u, vector<int>& colore, vector<int>& stackric, vector<int>& cammino){
    colore[u] = 1;
    stackric[u] = 1;
    cammino.push_back(u);
    int i=1;
    for(const Arco& arco: adjList[u]){
        int v=arco.d;
        if(stackric[v]==1){
            cout<<i<<") ciclo trovato: ";
            bool iniziato = false;
            for(int nodo : cammino){
                if(nodo == v) iniziato = true;
                if(iniziato) cout<<nodo<< " -> ";
            }
            cout<<v<<endl;
        }
        else if(colore[v] == 0){
            DFS_cicli(v, colore, stackric, cammino);
        }
    }
    stackric[u] = 0;
    cammino.pop_back();
    colore[u] = 2;
}

int main()
{
    ifstream input("input.txt");
    if(!input.is_open())
        cout<<"errore apertura file"<<endl;
    Grafo grafo;
    input >> grafo.nodi >> grafo.archi;
    grafo.adjList.resize(grafo.nodi+1);
    for (int i=0; i < grafo.archi; i++){
        int src,dst,peso;
        input >> src >> dst >> peso;
        grafo.adjList[src].push_back(Arco(dst,peso));
    }
    input.close();
    cout<<"grafo caricato"<<endl;

    grafo.TP_DFS();

    vector<int> res = grafo.Bellman_ford(4,2);
    if(!res.empty()){
        for(int i=0;i<res.size();i++){
            cout<<res[i];
            if(i<res.size()-1){
                cout<<" -> ";
            }
        }
        cout<<endl;
    }

    grafo.Trova_cicli();
    return 0;
}
