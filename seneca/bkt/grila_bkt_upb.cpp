#include <fstream>
#include <iostream>
using namespace std;

int x[10] ,n;

int contorSolutie = 1;
int Solutie(int k){
    
    return 1; // sau 0
}

int OK(int k){
    if (k > 7) {
      return 0;
    }
    // daca X e construit corect;
    for(int i = 1; i < k; i += 1) {
      if (x[i] >= x[k]) {
        return 0;
      }
    }
    return 1; // sau 0
}

void Afisare(int k)
{
  cout << "solutie ( " << contorSolutie << ") = " ;
  contorSolutie += 1;
  for(int i = 1; i <= k; i += 1) {
    cout << x[i] << " ";
  }
  cout << endl;
    // afișare/prelucrare soluția finală curentă
}

void Back(int k){    
  for(int i = 1 ; i <= 7 ; ++i)
    {
        x[k]=i;
        if(OK(k)) {
            if(Solutie(k))
                Afisare(k);
            Back(k+1);
        }
    }
}
int main(){
    //citire date de intrare
    Back(1);
    return 0;
}