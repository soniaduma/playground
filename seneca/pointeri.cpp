#include <iostream>
using namespace std;


// returneaza cat mai multe valori 
// valorile returnate sunt 1,2,3,4....10

// functiile urmatoare sunt absolut identice
int functie(int *x) 
{
  *(x + 0) = 2; 
  *(x + 1) = 3;
  *(x + 2) = 4;
  return 1;
}





1 
1 2
1 2 3
1 2 3 4
1 2 3 4 5 <-
1 2 3 4 5 6 <-
1 2 3 4 5 6 7 |
1 2 3 4 5 7 |
1 2 3 4 6
1 2 3 4 6 7 |
1 2 3 4 7

int aceeasi_functie(int x[]) 
{
  x[0] = 2;
  x[1] = 3;
  x[2] = 4;
  return 1;
}

// orice se intampla cu a,b,c va fi modificat direct la 
// referinta variabilelor unde sunt trimise ca parametru
int fn3(int &a, int &b, int &c) 
{
  // 
  a = 2;
  b = 3;
  c = 4;
  return 1;
}

int fn2(int *a, int *b, int *c) 
{
  // 
  *a = 2;
  *b = 3;
  *c = 4;
  return 1;
}

int main() {
  int x[100];
  memset(x, 0, 100 * sizeof(int));
  cout << aceeasi_functie(x); // 1
  cout << " " << x[0] << " " << x[1] << " " << x[2] << endl; // 
}