#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;


#define NUMAR_CARACTERE 4

char cuvantPartial[10];
/*
Utilizând metoda backtracking se generează în ordine lexicografică 
cuvintele de câte patru litere din mulţimea A={a,b,c,d,e}, cuvinte 
care nu conţin două vocale alăturate. Primele opt cuvinte generate sunt, 
în ordine: abab, abac, abad, abba, abbb, abbc, abbd, abbe.
*/

int cnt = 0;
bool SolutieFinala(int adancime){
  if(adancime == NUMAR_CARACTERE)
  {
    return true;
  }
  return false;
}

bool eVocala(char x) {
  return x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u';
}

// la pasul 1 trebuie sa fie mereu 'b'
// la pasul 4 trebuie sa fie mereu 'e'
bool OK(int adancime)
{
  // if (adancime == 1 && cuvantPartial[1] != 'b') return false;
  // if (adancime == 4 && cuvantPartial[4] != 'e') return false;
  return !(eVocala(cuvantPartial[adancime]) 
   && eVocala(cuvantPartial[adancime-1]));
}

int nrSolutii = 0;
void Afisare(int adancime)
{
  cout << "solutie (" << nrSolutii++ << ") = ";
  for(int i = 1; i <= adancime; i += 1) {
    cout << cuvantPartial[i];
  }
  cout << endl;
}

// adancime = a cata cifra o iterez
void BKT(int adancime){ 
  for(char i = 'a'; i <= 'e'; i += 1) {
    // pentru fiecare cifra posibila
    cuvantPartial[adancime] = i;
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
  cuvantPartial[9] = '\0';
    //citire date de intrare
    BKT(1);
    cout << "fefe";
    return 0;
}