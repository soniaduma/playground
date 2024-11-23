#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;


#define LENGTH 3

int cifre[10];
/*
Exercițiul #383
Utilizând metoda backtracking sunt generate numerele de 3 cifre, 
având toate cifrele în ordine strict crescătoare şi cu proprietatea că 
cifrele aflate pe poziţii consecutive sunt de paritate diferită. Ştiind 
că primele cinci soluţii generate sunt, în această ordine, 123, 125, 127, 
129, 145, care este cel de al 8-lea număr generat?
*/

int cnt = 0;
bool SolutieFinala(int adancime){
  if(adancime == LENGTH)
  {
    int sum = 0;
    for (int i = 1; i <= adancime; i += 1) {
      sum += cifre[i];
    }
    
    if (sum == 12)
      return true;
  }
  return false;
}


// la pasul 1 trebuie sa fie mereu 'b'
// la pasul 4 trebuie sa fie mereu 'e'
bool OK(int adancime)
{
  if (adancime == 1) return true;
  return ( cifre[adancime] > cifre[adancime-1] && 
        (cifre[adancime] + cifre[adancime-1]) % 2 == 1);
}

int nrSolutii = 0;
void Afisare(int adancime)
{
  cout << "solutie (" << ++nrSolutii << ") = ";
  for(int i = 1; i <= adancime; i += 1) {
    cout << cifre[i];
  }
  cout << endl;
}

// adancime = a cata cifra o iterez
void BKT(int adancime){ 
  if(adancime > LENGTH) return;

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
  cifre[9] = '\0';
    //citire date de intrare
    BKT(1);
    cout << "fefe";
    return 0;
}