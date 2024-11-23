#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


struct node{
  int target;
  int cost;
};  

vector<node> muchii[100];
ifstream fin("date.in");
ofstream fout("date.out");
int n,m ;

void print_graf_debug() {
  for(int i = 1; i <=n ; i += 1) {
    for(int j = 0; j < muchii[i].size(); j += 1) {
      cout << "am muchie de la " << i << " la " << muchii[i][j].target << " cu cost " << muchii[i][j].cost << endl;
    }
  }
}



void printVector(const char* nume, vector<int> &v) {
  cout << nume << ": [";
  for(int i = 0; i < v.size(); i += 1) {
    cout << v[i] << ", ";
  }
  cout << "]\n";
}

// returneaza true daca cautat exista in v
bool existaInVector(vector<int> v, int cautat) {
  for(int i = 0; i < v.size(); i += 1) {
    if (cautat == v[i]) return true;
  }
  return false;
}

// returneaza costul minim gasit pt constructia arborelui de cost minim
int algoritmPrim() {
  vector<int> noduriSelectate;
  int costMuchiiTotal = 0;
  noduriSelectate.push_back(1);

  while(noduriSelectate.size() != n) {
    // caut muchia minima dintr-un nod selectat intr-un nod neselectat
    int costMinimGasit = 9999999;
    int vecinMinimGasit = 192391;
    for(int i = 0; i < noduriSelectate.size(); i += 1) {
      int nodSelectat = noduriSelectate[i];
      // pt fiecare muchie din fiecare nod din cele selectate
      for(int j = 0; j < muchii[nodSelectat].size(); j ++) {
        int target = muchii[nodSelectat][j].target; // vecin
        int cost = muchii[nodSelectat][j].cost; // vecin

        // daca target e deja selectat, e muchie de la selectat la selectat
        // drop
        if (existaInVector(noduriSelectate, target)) {
          continue; // exista deja vecinul, este selectat deja
        }
        else {
          // este o muchie intre un selectat si un neselectat
          // trebuie sa vad daca are cost mai mic decat cea salvata in costMinim
          if (costMinimGasit > cost) {
            costMinimGasit = cost;
            vecinMinimGasit = target;
          }
        }
      }
    }

    cout << "Am selectat nodul " << vecinMinimGasit << " cu costul " << costMinimGasit << endl;
    costMuchiiTotal += costMinimGasit;
    noduriSelectate.push_back(vecinMinimGasit);
  }

  return costMuchiiTotal;
}


struct MuchieGenerica {
  int nod_a;
  int nod_b;
  int cost;
};

void debug_print_muchii_generice(vector<MuchieGenerica> v) {
  cout <<" muchii: [ ";
  for (int i = 0; i < v.size(); i += 1) {
    cout << "{" << v[i].nod_a << ", " << v[i].nod_b << ", " << v[i].cost << "},";
  }
  cout << " ]\n";

}


bool cmpFunction (MuchieGenerica i,MuchieGenerica j) { return (i.cost<j.cost); }

int kruskal() {

  vector<MuchieGenerica> muchiiLaGramada;

  int costTotal = 0;
  for(int i = 1; i <= n; i += 1) {
      // pt fiecare muchie din fiecare nod din cele selectate
    for(int j = 0; j < muchii[i].size(); j ++) {
      int target = muchii[i][j].target; // vecin
      int cost = muchii[i][j].cost; // vecin
      MuchieGenerica muchie;
      muchie.nod_a = i;
      muchie.nod_b = target;
      muchie.cost = cost;
      muchiiLaGramada.push_back(muchie);
    }
  }
  sort(muchiiLaGramada.begin(), muchiiLaGramada.end(), cmpFunction);

  int paduri[n];
  for (int i = 1; i <=n ; i += 1) {
    paduri[i] = i ;
  }
  for (int i = 0; i < muchiiLaGramada.size() ; i += 1) {
    // daca leaga doua paduri identice, skip
    MuchieGenerica muchie = muchiiLaGramada[i];
    if (paduri[muchie.nod_a] == paduri[muchie.nod_b]) {
      continue;
    } 

    cout << "aleg muchia {" << muchie.nod_a << ", " << muchie.nod_b << ", " << muchie.cost << "}\n";

    costTotal += muchie.cost;
    int paduriaPeCareOTransform = paduri[muchie.nod_b];

    // toate nodurile din paduria nod_b devin paduria nod_a:
    for (int i = 1; i <= n; i += 1) {
      if (paduri[i] == paduriaPeCareOTransform) {
        paduri[i] = paduri[muchie.nod_a];
      }
    }
  }
  
  return costTotal;
}
int main() {

  fin >> n >> m;
  for (int i = 1; i <= m; i += 1) {
    int nod, target, cost;
    node x;
    fin >> nod >> target >> cost;
    node x1; x1.target = target; x1.cost = cost;
    node x2; x2.target = nod; x2.cost = cost;
  
    muchii[nod].push_back(x1);
    muchii[target].push_back(x2);
  }
  //print_graf_debug();

  int rez = kruskal();
  cout << "Raspuns final: " << rez << endl;

  return 0;
}