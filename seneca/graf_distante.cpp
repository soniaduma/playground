#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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
void dijkstra(int startNode = 1) {
  vector<int> coada;
  int d[100]; // d[i] este distanta de la startnode la i
  memset(d, 999999, 100 * sizeof(int));

  d[startNode] = 0;

  coada.push_back(startNode);
  while(!coada.empty()) {
    // iau urmatorul nod
    int minimAlesPoz = 0;
    for(int i = 1; i < coada.size(); i += 1) {
      if(d[coada[i]] < d[coada[minimAlesPoz]]) {
        minimAlesPoz = i;
      }
    }

    int nodMinimAles = coada[minimAlesPoz];
    coada.erase(coada.begin() + minimAlesPoz);
    cout << "alegem nodul " << nodMinimAles << " din coada\n";

    // pentru toti vecinii lui nod minim ales:
    for(int i = 0; i < muchii[nodMinimAles].size(); i += 1) {
      int vecin = muchii[nodMinimAles][i].target;
      int cost = muchii[nodMinimAles][i].cost; // de la nod_a la nod_b


      if (cost + d[nodMinimAles] < d[vecin]) {
        d[vecin] = cost + d[nodMinimAles];
        cout << "gasit drum mai bun pana la " << vecin << " cu cost: " << d[vecin] << endl;
        bool existaInCoada = false;
        // adaug vecin in pr. coada daca nu exista
        for(int j = 0;  j < coada.size(); j += 1) {
          if (coada[j] == vecin) {
            existaInCoada = true;
            break;
          }
        }
        if (!existaInCoada) {
          cout << "am adaugat in coada pe " << vecin << endl;
          coada.push_back(vecin);
        }
      }
    }
    printVector("Priority queue", coada);

  }
  for (int i = 1; i <= n; i += 1) {
    cout << "d[" << i << "] = " << d[i] << endl;
  }
}

void bfs(int startNode = 1) {
  bool viz[100];
  for(int i = 1; i <= n ; i += 1) {
    viz[i] = false;
  }

  queue<node> coada;
  node payload;
  payload.target = startNode;
  payload.cost = 0;
  coada.push(payload);
  viz[startNode] = true;
  while(!coada.empty()) {
    // iau urmatorul nod
    node nod = coada.front();

    cout << "Vizitez " << nod.target << " cu costul " << nod.cost << endl;
    // scot urmatorul nod din queue:
    coada.pop();

    // pun toti vecinii nevizitati inca ai nodului curent in queue:
    for(int i = 0; i < muchii[nod.target].size(); i += 1) {
      int vecin = muchii[nod.target][i].target;
      if(!viz[vecin]) {
        cout << "bagat in coada pe " << vecin << endl;
        node payload_queue;
        payload_queue.target = vecin;
        payload_queue.cost = nod.cost + 1;
        coada.push(payload_queue);
        viz[vecin] = true;
      } else {
        cout << " ba e ciclu " << vecin << endl;
      }
    }
  }
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
  // print_graf_debug();

  // bfs(6);

  dijkstra(10);

  return 0;
}