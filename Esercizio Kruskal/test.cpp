#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class edge{
    public:
        int src, dst, w;
        edge(int src, int dst, int w): src(src), dst(dst), w(w) {}
};

class grafo{
    public:
        vector<edge> edges;
        int V,E;
        grafo(int vertici, int archi): V(vertici), E(archi) {};
        void add_edge(int u, int v, int w);
        int Kruskal(int E);
};

//grafo non orientato
void grafo::add_edge(int u, int v, int w){
    this->edges.push_back({u,v,w});
}

int find(vector<int>& parent, int i){
    if(parent[i] == -1)
        return i;
    return parent[i] = find(parent, parent[i]); // path compression
}

void Union (vector<int>& parent, int u, int v){
    int x = find(parent, u);
    int y = find(parent, v);
    parent[x] = y;
}

int grafo::Kruskal(int E){
    int mst = 0;
    sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.w<b.w; });
    vector<int> parent(V, -1);
    for(int i=0; i < E; i++){
        int u = edges[i].src;
        int v = edges[i].dst;
        int w = edges[i].w;
        int x = find(parent, u);
        int y = find(parent, v);
        if(x!=y){
            mst += w;
            cout<< "ho sommato l'arco di peso: "<<w<<endl;
            Union(parent, u , v);
        }
    }
    return mst;
}


int main(){
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    int V, E, mst = 0;
    inputFile >> V >> E;
    grafo G(V,E);
    int u,v,w;
    
    for(int i=0;i<E; i++){
        inputFile >> u >> v >> w;
        G.add_edge(u-1,v-1,w);
    }
    
    mst = G.Kruskal(E);
    outputFile << mst;
    
    inputFile.close();
    outputFile.close();
    return 0;
}