/*

Nome:Júlia Carvalho de Souza Castro
TIA: 32022298

*/
  
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <locale.h>
#include <limits>
#include <string>
#include <cstdlib>

using namespace std;
const int MAX = 255;

class TGrafo {
private:
  int n;     // quantidade de vértices
  int m;     // quantidade de arestas
  float **adj; // matriz de adjacência
  string array[100];
public:
  TGrafo(int n);
  void insereA(int v, int w, float a);
  void removeA(int v, int w);
  void show();
  void gravar();
  void ler();
  void inserirV(string r);
  void removeV(int v);
  void cont();
  void verif();
  void appEnd();
  ~TGrafo();
};

TGrafo::TGrafo(int n) {
  this->n = n;
  this->m = 0;
  ifstream file("example.txt");
  string line;

    int i = 0;

    if (file.is_open()) {
        while (getline(file, line, ';')) {
            array[i++] = line;
        file.ignore(); 
        }
        file.close();
    }

    
  float **adjac = new float *[n];
  for (int i = 0; i < n; i++)
    adjac[i] = new float[n];
  adj = adjac;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adj[i][j] = numeric_limits<float>::infinity();

}



TGrafo::~TGrafo() {
  n = 0;
  m = 0;
  delete[] * adj;
  cout << "espaço liberado";
}

void TGrafo::insereA(int v, int w, float a) {
  if (adj[v][w] == numeric_limits<float>::infinity()) {
    adj[v][w] = a;
    m++;
  }
  else
    cout << "Aresta já existente" <<endl;
}

void TGrafo::removeA(int v, int w) {
  if (adj[v][w] !=  numeric_limits<float>::infinity()) {
    adj[v][w] = numeric_limits<float>::infinity();
    m--;}
  else
    cout << "Aresta não existente" <<endl;
  }


void TGrafo::show() {
  for (int i = 0; i < n; i++)
      cout << i << " = " << array[i] << endl;
    
  cout << "n: " << n << endl;
  
  cout << "m: " << m << endl;
  for (int i = 0; i < n; i++) {
    cout << "\n";
    for (int w = 0; w < n; w++)
      if (adj[i][w] != numeric_limits<float>::infinity())
         cout << "(" << i << "," << w << ") = " << adj[i][w]<< " ";

  }

  cout << "\nfim da impressao do grafo." << endl;
}

void TGrafo::gravar() {
  ofstream fout("grafo.txt");
  fout << n << endl;
  
  for (int i = 0; i < n; i++) {

    fout << i <<" "<<array[i] << endl;
    }
  
  fout << m << endl;
  for (int i = 0; i < n; i++) {
    for (int w = 0; w < n; w++)
      
      if (adj[i][w] != numeric_limits<float>::infinity())
        fout << i << " " << adj[i][w] << " " << w << " " << endl;
  }
  ofstream fouti("grafo-matriz.txt");
  for (int i = 0; i < n; i++) {
    for (int w = 0; w < n; w++)
      if (adj[i][w] != numeric_limits<float>::infinity())
        fouti << i << " " << w << endl;
  }

}

void TGrafo::ler() {
  char buffer[MAX];
  ifstream fin("grafo.txt");
  while (!fin.eof()){
  fin.getline(buffer, MAX);
  cout << buffer << endl;
}
}


void TGrafo::inserirV(string r){

    ofstream file("example.txt", ios::app);
    file << r << ";" << endl;
    file.close();

  array[n]=r;
   n+=1;

  
  float **adjac = new float *[n];
  for (int w = 0; w < n; w++)
    adjac[w] = new float[n];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) 
      if ((i!=n-1) && (j!=n-1))
        adjac[i][j] = adj[i][j];
      else
        adjac[i][j] = numeric_limits<float>::infinity();
  adj = adjac;
}

void TGrafo::removeV(int v){
  n-=1;

  for (int i = 0; i <= n; i++)
    if(i<v)
      array[i]=array[i];
    else
      array[i]=array[i+1];
  
    
  float **adjac = new float *[n];
  for (int i = 0; i <= n; i++)
    adjac[i] = new float[n];

  for (int w = 0; w < n; w++){
    removeA(v, w);
    removeA(w, v);}
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++){ 
        if (i<v){
          if (j<v)
            adjac[i][j] = adj[i][j];
          
          else
            adjac[i][j] = adj[i][j+1];
        }
        else
          if (j<v)
            adjac[i][j] = adj[i+1][j];
          
          else
            adjac[i][j] = adj[i+1][j+1];
        }
  adj = adjac;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) 
        adj[i][j] = adjac[i][j];

}

void TGrafo::cont() {
  cout << "Tipo: 2"<<endl;
    
  cout << "Numero de vertices: " << n << endl;
  
  cout << "Numero de arestas: " << m << endl;
  for (int i = 0; i < n; i++)
      cout<< i << " " << array[i] << endl;
  for (int i = 0; i < n; i++) {
    cout << "\n";
    for (int w = 0; w < n; w++)
      if (adj[i][w] != numeric_limits<float>::infinity())
         cout << "(" << i << "," << w << ") = " << adj[i][w]<< " ";

  }

  cout << "\nfim da impressao do grafo." << endl;
}

void TGrafo::verif() {
  std::string command = "python3 verify.py";
  std::system(command.c_str());
}

void TGrafo::appEnd() {
  std::string command = "python3 app-enderecos.py";
  std::system(command.c_str());
}

char buffer[MAX];
int main() {
   
  TGrafo g(40);
  
  g.insereA(0, 37, 4);
  g.insereA(0, 10, 11);
  g.insereA(0, 19, 20);
  g.insereA(1, 30, 7);
  g.insereA(1, 39, 4);
  g.insereA(1, 7, 4);
  g.insereA(2, 6, 8);
  g.insereA(2, 27, 8);
  g.insereA(2, 34, 14);
  g.insereA(3, 11, 4);
  g.insereA(3, 28, 11);
  g.insereA(3, 21, 3);
  g.insereA(4, 21, 4);
  g.insereA(4, 3, 8);
  g.insereA(4, 17, 13);
  g.insereA(5, 12, 6);
  g.insereA(5, 35, 8);
  g.insereA(5, 33, 13);
  g.insereA(6, 11, 4);
  g.insereA(6, 39, 11);
  g.insereA(6, 9, 12);
  g.insereA(7, 20, 4);
  g.insereA(7, 19, 8);
  g.insereA(7, 25, 6);
  g.insereA(8, 20, 13);
  g.insereA(8, 19, 13);
  g.insereA(8, 25, 17);
  g.insereA(9, 3, 6);
  g.insereA(9, 19, 3);
  g.insereA(9, 8, 11);
  g.insereA(10, 38, 3);
  g.insereA(10, 37, 2);
  g.insereA(10, 25, 17);
  g.insereA(11, 1, 7);
  g.insereA(11, 8, 12);
  g.insereA(11, 31, 12);
  g.insereA(12, 16, 5);
  g.insereA(12, 13, 7);
  g.insereA(12, 29, 8);
  g.insereA(13, 12, 5);
  g.insereA(13, 32, 6);
  g.insereA(13, 15, 10);
  g.insereA(14, 2, 3);
  g.insereA(14, 11, 4);
  g.insereA(14, 21, 6);
  g.insereA(15, 11, 4);
  g.insereA(15, 14, 6);
  g.insereA(15, 18, 11);
  g.insereA(16, 0, 11);
  g.insereA(16, 5, 10);
  g.insereA(16, 15, 7);
  g.insereA(17, 20, 7);
  g.insereA(17, 28, 14);
  g.insereA(17, 36, 10);
  g.insereA(18, 17, 13);
  g.insereA(18, 2, 3);
  g.insereA(18, 22, 7);
  g.insereA(19, 14, 6);
  g.insereA(19, 36, 13);
  g.insereA(19, 26, 12);
  g.insereA(20, 34, 17);
  g.insereA(20, 14, 6);
  g.insereA(21, 34, 17);
  g.insereA(21, 14, 6);
  g.insereA(22, 6, 7);
  g.insereA(22, 10, 6);
  g.insereA(23, 7, 27);
  g.insereA(23, 8, 10);
  g.insereA(24, 6, 16);
  g.insereA(24, 18, 7);
  g.insereA(25, 0, 14);
  g.insereA(25, 17, 5);
  g.insereA(26, 3, 13);
  g.insereA(26, 5, 16);
  g.insereA(27, 23, 11);
  g.insereA(27, 33, 12);
  g.insereA(28, 27, 2);
  g.insereA(28, 13, 3);
  g.insereA(29, 23, 11);
  g.insereA(29, 33, 12);
  g.insereA(30, 29, 4);
  g.insereA(30, 31, 6);
  g.insereA(31, 24, 13);
  g.insereA(31, 7, 4);
  g.insereA(32, 7, 3);
  g.insereA(32, 1, 3);
  g.insereA(33, 16, 12);
  g.insereA(33, 9, 11);
  g.insereA(34, 16, 10);
  g.insereA(34, 4, 15);
  g.insereA(35, 22, 12);
  g.insereA(35, 1, 5);
  g.insereA(36, 15, 10);
  g.insereA(36, 13, 11);
  g.insereA(37, 4, 11);
  g.insereA(37, 32, 12);
  g.insereA(38, 0, 5);
  g.insereA(38, 12, 9);
  g.insereA(39, 35, 7);
  g.insereA(39, 5, 1);
  
char b;
int v1, v2;
float a;
string r1;


while (b != 'i'){
  cout << "\n ------------------------------ \n | Projeto de teoria de Grafos | \n ------------------------------\n \n \n +   Esse trabalho se relaciona com os objetivos ODS 11 e 13,\n pois tem como objetivo a diminuição da emissão de gases \n poluentes pelos veiculos que fazem entregas em diversos \n endereços consecutivos.  \n \n ----------------------------------------------------------- \n \n Digite a letra correspondente a função que deseja executar: \n \n "<< 
    "*Execute a opção b antes de executar qualquer outra!* \n \n a -> Ler dados do arquivo grafo.txt\n b -> Gravar dados no arquivo grafo.txt\n c -> Inserir vértice\n d -> Inserir aresta;\n e -> Remove vértice;\n f -> Remove aresta;\n g -> Mostrar conteúdo do arquivo;\n h -> Mostrar grafo;\n i -> Encerrar a aplicação. \n j -> Verificar conexividade \n k -> Otimização da ordem do percurso das entregas.\n \n" << endl;
  cin >> b;
  switch(b) {

  case 'a':
    g.ler();
    break;
    
  case 'b':
    g.gravar();
    // code block
    break;

  case 'c':
    cout<<"\nInsira o nome da rua: ";
    cin.ignore();
    getline(cin, r1);
    g.inserirV(r1);
    break;

  case 'd':
      cout<<"\nInsira o primeiro vertice: ";
      cin >> v1;
      cout<<"\nInsira o segunto vertice: ";
      cin >> v2;
      cout<<"\nInsira a aresta: ";
      cin >> a;
      g.insereA(v1, v2, a);
      break;

  case 'e':
    cout<<"\nInsira o vertice que gostaria de apagar: ";
    cin >> v1;
    g.removeV(v1);
    break;
    
  case 'f':
    cout<<"\nInsira o primeiro vertice: ";
    cin >> v1;
    cout<<"\nInsira o segunto vertice: ";
    cin >> v2;
    g.removeA(v1, v2);
    break;

  case 'g':
    g.cont();
    break;
    
  case 'h':
    g.show();
    break;
    
  case 'i':
      
    cout<<"bye bye!!"<< endl;
    break;
  
  case 'j':
    g.verif();
    break;

  case 'k':
    g.appEnd();
    break;
  
  default:
    cout << "\n opção invalida, tente novamente" << endl;
    break;
    // code block
}}
  return 0;
}
