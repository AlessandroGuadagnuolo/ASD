#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Nodo{
public:
    int chiave;
    char carattere;
    Nodo* sx;
    Nodo* dx;
    Nodo* parent;
    Nodo(int k,char c): chiave(k), carattere(c), sx(nullptr), dx(nullptr) , parent(nullptr) {}
};

class ABR{
public:
    Nodo* radice;
    ABR(): radice(nullptr){}
    void insert(Nodo*& nodo,int chiave, char carattere, Nodo* parent);
    void successore(Nodo*& X);
    void leftRotate(Nodo*& X);
    void stampa(Nodo* nodo);
    void transplant(Nodo* u, Nodo* v);
};

void ABR::insert(Nodo*& nodo,int key, char c, Nodo* p){

    if(nodo==nullptr)
    {
        nodo = new Nodo(key,c);
        nodo->parent = p;
        return;
    }
    if(key < nodo->chiave){
        insert(nodo->sx,key,c,nodo);
    }
    else{
        insert(nodo->dx,key,c,nodo);
    }
}

void ABR::successore(Nodo*& X){
    if(X==nullptr){
        cout<<"Nodo non valido"<<endl;
        return;
    }
    Nodo* succ = nullptr;


    if(X->dx!=nullptr){
        succ = X->dx;
        while(succ->sx!=nullptr){
            succ = succ->sx;
        }
    }

    else{
        Nodo* curr = radice;
        while(curr != nullptr){
            if(X->chiave < curr->chiave){
                succ = curr;
                curr = curr->sx;
            }
            else if(X->chiave > curr->chiave){
                curr = curr->dx;
            }
            else break;
        }
    }

    ofstream output("OUT.txt");
    if (succ!= nullptr){
        output<<"<"<<succ->chiave<<","<<succ->carattere<<">"<<endl;
    }
    else{
        output<<"Nessun successore";
    }
    output.close();
}

void ABR::leftRotate(Nodo*& X)
{
    if(X==nullptr || X->dx == nullptr) {
        cout<<endl<<"Non e' possibile fare la left rotate"<<endl;
        return;
    }

    Nodo* y = X->dx;
    X->dx = y->sx;
    if(y->sx!=nullptr){
        y->sx->parent = X;
    }

    y->parent = X->parent;

    if(X->parent == nullptr){
        radice = y;
    }
    else if(X==X->parent->sx){
        X->parent->sx = y;
    }
    else X->parent->dx = y;

    y->sx = X;
    X->parent = y;
}

void ABR::stampa(Nodo* nodo) {
    if (nodo == nullptr) return;
    cout << "<" << nodo->chiave << "," << nodo->carattere << "> ";
    stampa(nodo->sx);
    stampa(nodo->dx);
}

void ABR::transplant(Nodo* u, Nodo* v){
    if(v != nullptr && v->parent != nullptr){
        if(v->parent->sx == v) v->parent->sx = nullptr;
        else if(v->parent->dx == v) v->parent->dx = nullptr;
    }
     if (u->parent == nullptr) {
        radice = v;
    }
    else if (u == u->parent->sx)
        u->parent->sx = v;
    else
        u->parent->dx = v;

    if (v != nullptr) {
        v->parent = u->parent;
    }
}


int main()
{
    ifstream input("ABR.txt");

    int chiave;
    char c;
    ABR abr;
    while(input >> chiave >> c){
        abr.insert(abr.radice, chiave, c, nullptr);
    }
    input.close();

    Nodo* X = abr.radice->dx;
    Nodo* Y = abr.radice->sx;

    abr.successore(X);

    cout << "Prima della left rotate:" << endl;
    abr.stampa(abr.radice);
    cout << endl;

    abr.leftRotate(X);

    cout << "Dopo la left rotate:" << endl;
    abr.stampa(abr.radice);
    cout << endl << "--------------------------------" << endl;


    X = abr.radice->sx;
    Y = abr.radice->dx;

    cout << "Prima della transplant:" << endl;
    abr.stampa(abr.radice);
    cout << endl;

    abr.transplant(X, Y);

    cout << "Dopo la transplant:" << endl;
    abr.stampa(abr.radice);
    cout << endl;

    return 0;
}
