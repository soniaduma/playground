#include <iostream>
using namespace std;

#define PRECISION 0.01

double sqrt(double n) {

  // cat timp NU (x^2 <= n <= x^2 + precision) 

  double x;
  double lowerBound = 0, upperBound = n;
  x = (lowerBound + upperBound)/2;

  while ( ! (x * x <= n && x * x + PRECISION >= n) ) {
    if (x * x > n) {
      upperBound = x;
      x = (lowerBound + upperBound)/2;
    } else {
      lowerBound = x;
      x = (lowerBound + upperBound)/2;
    }
    
  }
  return x;
  // returneaza radical(n) cu precizie de 2 zecimale
}

// sqrt(4.01) -> 2
// sqrt(5) -> 2.23 e ok de returnat


void test(double n) {
  cout << "sqrt(" << n << ") = " << sqrt(n) << endl;
}
int main() {
  test(5);
  test(13);
  test(192389);
}