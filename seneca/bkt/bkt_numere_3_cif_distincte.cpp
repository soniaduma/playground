#include <fstream>
#include <iostream>
using namespace std;

int cifre[10];

#define NUMAR_CIFRE 6

bool SolutieFinala(int adancime){
  if(adancime == NUMAR_CIFRE) {
    return true;
  }
  return false;
}

bool OK(int adancime){
  for(int i = 1; i < adancime; i += 1) {
    if(cifre[i] == cifre[adancime]) {
      return false;
    }
  }
  return true;
}

int nrSolutii = 0;
void Afisare(int adancime)
{
  cout << "solutie (" << nrSolutii++ << ") = ";
  for(int i = 1; i <= adancime; i += 1) {
    cout << cifre[i];
  }
  cout << endl;
}

// adancime = a cata cifra o iterez
void BKT(int adancime){ 
  for(int i = (adancime == 1 ? 1 : 0); i <= 9; i += 1) {
    // pentru fiecare cifra posibila
    cifre[adancime] = i;
    if(OK(adancime)) {
      if(SolutieFinala(adancime)) {
        Afisare(adancime);
      } else {
        BKT(adancime + 1);
      }
    }
  }
}
int main(){
    //citire date de intrare
    BKT(1);
    return 0;
}