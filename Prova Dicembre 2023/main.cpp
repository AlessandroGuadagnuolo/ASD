#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class elem{
public:
    int key;
    string value;
    elem(int k, string v): key(k), value(v) {}
};

class HashTable{
public:
    vector<elem*> table;
    int dim;
    HashTable(int dim): dim(dim) { table.resize(dim,nullptr); }
    int lineare(int key,int i){
        return(key+i) % dim;
    }

    void insert(elem* x);
    void PRINT(ofstream& output);
    void FIND(int k);
    void DELETE(int k);
};

void HashTable::insert(elem* x){
    int i=0;
    while(i<dim){
        int j = lineare(x->key,i);
        if(table.size() <= j){
            table.resize(j+1,nullptr);
        }

        if(table[j]==nullptr){
            table[j] = x;
            return;
        }
        i++;
    }
    cout<<"Error"<<endl;
}

void HashTable::PRINT(ofstream& output){
    for(int i=0; i < dim; i++){
        if(table[i]!= nullptr){
            output<<"<"<<table[i]->key<<","<<table[i]->value<<">"<<endl;
        }
    }
}

void HashTable::FIND(int k){
    int i=0;
    while(i<dim){
        int j = lineare(k,i);
        if(table[j]==nullptr) break;
        if(table[j]->key == k){
            cout<<"Stringa trovata: "<<table[j]->value<<endl;
            return;
        }
        i++;
    }
    cout<<"Stringa non trovata"<<endl;
}

void HashTable::DELETE(int k){
    int i=0;
    while(i<dim){
        int j = lineare(k,i);
        if(table[j]!=nullptr && table[j]->key == k){
            delete table[j];
            table[j] = nullptr;
            cout<<"Elemento eliminato dalla table"<<endl;
            for(int i=0; i<dim; i++){
                if(table[i]!=nullptr) cout<<"<"<<table[i]->key<<","<<table[i]->value<<">"<<endl;
                else cout<<"------------"<<endl;
            }
            return;
        }
        i++;
    }
    cout<<"Elemento da eliminare non trovato"<<endl;
}

int main()
{
    ifstream input("IN.txt");
    HashTable ht(23);

    int key;
    string parola, line;

    while(getline(input,line)){
        stringstream ss(line);
        char ignore;
        ss>>ignore>>key>>ignore;
        getline(ss,parola,'>');
        elem* x = new elem(key,parola);
        ht.insert(x);
    }

    ofstream output("OUT.txt");
    ht.PRINT(output);
    ht.FIND(7);
    ht.DELETE(7);
    ht.FIND(7);
    return 0;
}
