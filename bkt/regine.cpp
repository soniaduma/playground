// CodeCall.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("Date.in");
ofstream fout("Date.out");

#define cout fout

// - care e numarul maxim de regine pe care il putem pune?
// - in cate moduri le putem pune?
// regine cat mai multe regine fara ca oricare 2 regine sa se atace intre ele

// matrice NMAX x NMAX
#define NMAX 10

// forta bruta-bruta: toate combinatiile posibile, niciun rafinament:

// toate combinatiile posibile de pus regine:

int MAX_VALUE = (1 << (NMAX * NMAX));


void printBiti(int numar) {
	// afisez frumos cei 16 biti
	cout << "numar = ";

	for (int i = (NMAX * NMAX) - 1; i >= 0 ; i -= 1) {
		cout <<  (bool)((numar & (1 << i)));
		if (i % NMAX == 0 && i) {
			cout << " ";
		}
	}
	cout << endl;
}

void printTabla(bool mat[NMAX][NMAX]) {
	cout << "TABLA SAH:\n";
	for (int i = 0; i < NMAX; i += 1) {
		for (int j = 0; j < NMAX; j += 1) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------\n";
}

// returneaza true daca se ataca;
bool seAtaca(bool mat[NMAX][NMAX], int i, int j) {
	if (!mat[i][j]) return false; // cine dracu se ataca, ma????

	// se ataca pe linie?
	for (int k = 0; k < NMAX; k += 1) {
		if (k == j) {
			continue;
		}
		if (mat[i][k]) {
			return true;
		}
	}


	// se ataca pe coloana?
	for (int k = 0; k < NMAX; k += 1) {
		if (k == i) {
			continue;
		}
		if (mat[k][j]) {
			return true;
		}
	}
	
	// se ataca pe diagonala - sus stanga
	for (int k = 1; i-k >= 0 && j - k >= 0; k++) {
		if (mat[i-k][j-k]) {
			return true;
		}
	}

	// se ataca pe diagonala - sus dreapta
	for (int k = 1; i - k >= 0 && j + k < NMAX; k++) {
		if (mat[i - k][j + k]) {
			return true;
		}
	}
	// se ataca pe diagonala - jos stanga
	for (int k = 1; i + k < NMAX && j - k >= 0; k++) {
		if (mat[i + k][j - k]) {
			return true;
		}
	}

	// se ataca pe diagonala - jos dreapta
	for (int k = 1; i + k < NMAX && j + k < NMAX; k++) {
		if (mat[i + k][j + k]) {
			return true;
		}
	}

	return false;
	// se ataca pe diagonala 2?

}
bool solutie(int numar) {
	// verifica daca state-ul definit de numar pe matrice este corect
	bool mat[NMAX][NMAX];
	for (int i = 0; i < NMAX; i += 1) {
		for (int j = 0; j < NMAX; j += 1) {
			mat[i][j] = numar & (1 << (NMAX * NMAX - 1 - NMAX * i - j));
		}
	}

	// ba se ataca vreo regina cu vreo alta regina???

	for (int i = 0; i < NMAX; i += 1) {
		for (int j = 0; j < NMAX; j += 1) {
			if (seAtaca(mat, i, j)) {
				return false;
			}
		}
	}

	cout << "am gasit solutie: ";
	printTabla(mat);
	return true;
}

int main_forta_bruta_bruta()
{
	int mat[NMAX][NMAX];

	// toate numerele posibile de la 0 la 2 ^ (NMAX * NMAX)

	int max = (1 << (NMAX * NMAX));
	//for (int i = 0; i < MAX_VALUE; i += 1) {
	for (int i = 0; i < MAX_VALUE; i += 1) {
		solutie(i);
	}
	return 0;
}


bool mat[NMAX][NMAX]; // matricea - tabla de sah

// returneaza daca e okay state-ul curent
bool okBkt(int i, int j) {
	if (seAtaca(mat, i, j)) {
		return false;
	}
	return true;
}



// daca cerinta ar fi "toate felurile in care pot sa pun minim 2 regine":
// solutie() verifica ca sunt minim 2 regine
bool solutieBkt(int n) {
	return n >= NMAX;
	// returneaza ca state-ul corect partial, care e deja OKAY(), are si minim 2 regine in el
}

void afiseazaBkt() {
	printTabla(mat);
}
void bkt(int n, int startI = 0) { // n = adancime
	// pentru fiecare pozitie posibila
	for (int i = startI; i < NMAX; i += 1) {
		for (int j = 0; j < NMAX; j += 1) {
			// incerc sa pun regina la pozitia [i][j];
			if (mat[i][j]) {
				continue;
			}

			mat[i][j] = true;
			if (okBkt(i, j)) {
				if (solutieBkt(n)) {
					afiseazaBkt();
				}
				bkt(n + 1, i);
			}
			mat[i][j] = false;
		
		}
	}
}
int main() {
	for (int i = 0; i < NMAX; i += 1){
		for (int j = 0; j < NMAX; j += 1) {
			mat[i][j] = false;
		}
	}
	bkt(1);
	return 0;
}
