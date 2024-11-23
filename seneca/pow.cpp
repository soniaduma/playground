#include <iostream>
using namespace std;


/*
  RIDICAREA LA PUTERE IN TIMP LOGARITMIC
*/

double pow(double nr, int putere, int &debug_pasi) 
{
  debug_pasi ++;
  if (putere == 1) return nr;
  if(putere % 2 == 0)
  {
    return  pow(nr * nr, putere/2, debug_pasi);
  }
  return nr * pow(nr, putere-1, debug_pasi);
}

// sqrt(4.01) -> 2
// sqrt(5) -> 2.23 e ok de returnat


void test(double n, int p) {
  int pasi;
  cout << "pow(" << n << ", " << p <<") = " << pow(n, p, pasi) 
    << "; facut in " << pasi << " pasi !" << endl;
}
int main() {
  test(5,7);
  test(3,5);
  test(1.0001,102130);
}