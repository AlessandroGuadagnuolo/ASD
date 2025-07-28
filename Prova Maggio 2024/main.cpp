#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;

class Nodo{
public:
    int chiave;
    char carattere;
    Nodo* sx;
    Nodo* dx;

    Nodo(int key, char c): chiave(key), carattere(c), sx(nullptr), dx(nullptr) {}
    ~Nodo(){
        delete sx;
        delete dx;
    }
};

class ABR{
public:
    Nodo* radice;
    ABR(): radice(nullptr) {}
    void insert(Nodo*& nodo, int chiave,char carattere);
    void visitPreorder(Nodo* n,ofstream& output);
    map<char,string> codifica;
    string Huffman(string stringa);
    void Decodifica(Nodo* radice, string stringa);
};

void ABR::insert(Nodo*& nodo, int chiave, char c){
    if(nodo==nullptr){
        nodo = new Nodo(chiave, c);
        return;
    }
    if(chiave < nodo->chiave){
        insert(nodo->sx,chiave,c);
    }
    else{
        insert(nodo->dx,chiave,c);
    }
}

void ABR::visitPreorder(Nodo* n,ofstream& output){
    if(n==nullptr){
        return;
    }
    output<<n->carattere<<" ";
    visitPreorder(n->sx,output);
    visitPreorder(n->dx,output);
}

void Build_codifica(Nodo* nodo,string codice, map<char,string>& codifica){
    if(nodo==nullptr) return;

    if(nodo->carattere != '*'){
        codifica[nodo->carattere] = codice;
    }

    Build_codifica(nodo->sx,codice+"0",codifica);
    Build_codifica(nodo->dx,codice+"1",codifica);
}

string ABR::Huffman(string stringa){
    map<char,string> codifica;
    string risultato;
    Build_codifica(radice,"",codifica);
    cout<<"Stringa codificata: ";
    for(auto ch:stringa){
        if(codifica.count(ch)){
            cout<<codifica[ch];
            risultato += codifica[ch];
        }
    }
    cout<<endl;
    return risultato;
}

void ABR::Decodifica(Nodo* radice,string codice){
    Nodo* curr = radice;
    cout<<"Stringa decodificata: ";
    for(auto bit: codice){
        if(bit=='0')   curr=curr->sx;
        if(bit=='1')   curr = curr->dx;

        if(curr->carattere != '*'){
            cout<<curr->carattere;
            curr = radice;
        }
    }
    cout<<endl;
}

int main()
{
    ABR abr;
    ifstream input("ABR.txt");
    if(!input.is_open()){
        cout<<"errore apertura file."<<endl;
    }
    int chiave;
    char c;
    while(input>>chiave>>c){
        abr.insert(abr.radice,chiave,c);
    }
    input.close();
    ofstream output("OUT.txt");
    abr.visitPreorder(abr.radice,output);
    cout<<"visita preorder eseguita su file OUT"<<endl;
    output.close();

    string stringa = "ciaho";
    cout<<"Stringa: "<<stringa<<endl;
    string risultato = abr.Huffman(stringa);
    abr.Decodifica(abr.radice,risultato);
    return 0;
}
