#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> 
using namespace std;

void GameLoop();
void Level1();
void PrintMap();
void UpdateMap();

char originalMap[500][500]; // clean copy of the original map for clean game loop
ofstream fout("Game.out");

// daca vrei, te poti juca cu config-ul nivelului:
#define SCORE_DIFFICULTY_INCREASE_THRESHOLD 20 

char map[500][500];
int mapWidth, mapHeight;
int playerX, playerY;


#define PLAYER_MOVE_LEFT 1
#define PLAYER_MOVE_RIGHT 2
#define PLAYER_MOVE_UP 4
#define PLAYER_MOVE_DOWN 8
#define PLAYER_HORN 16 
// claxoneaza :) 

/* asta e singura functie in care trebuie sa scrii cod :)
// este apelata la fiecare mutare; trebuie sa citesti matricea (map[][]) sa vezi unde sunt obstacolele; te poti folosi doar de (map[][], playerX, playerY, mapWidth, mapHeight)

functia returneaza un set de instructiuni printr-o singura valoare, prin primii 5 biti ai valorii (de la dreapta la stanga). Fiecare bit poate fi 1 sau 0, unde valoarea 1 inseamna "true" pentru instructiunea respectiva.

bitii au urmatoarea reprezentare:

#define PLAYER_MOVE_LEFT 1  < cel mai din dreapta; daca e setat cu "1", inseamna ca instructiunea e ca masina sa se duca la stanga
#define PLAYER_MOVE_RIGHT 2 < al 2lea bit din dreapta; daca e setat cu "1", inseamna ca instructiunea e ca masina sa se duca la dreapta
#define PLAYER_MOVE_UP 4    < al 3lea bit, sus
#define PLAYER_MOVE_DOWN 8  < al 4lea bit
#define PLAYER_HORN 16      < claxoneaza

de ex, pentru valoarea 0b0011001, player-ul se va duce in stanga, in jos si va claxona in acelasi timp

*/
int playerMove() {
    //return 0;
    return PLAYER_MOVE_RIGHT;
}


int main()
{
    srand(time(NULL));
    Level1(); // todo more levels
    GameLoop();
    return 0;
}


class Obstacle {
public:

    Obstacle(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void Advance() {
        this->x += 1; //go down
    }

    bool Crash() {
        return this->x == playerX && this->y == playerY;
    }
    bool CanDestroy() {
        return this->x >= mapHeight;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Obstacle& obstacle) {
        stream << "Obstacle at position [" << obstacle.x << "," << obstacle.y << "]";
        return stream;
    }

    int x, y;
};

void ReadMap(const char* filename) {
    ifstream fin(filename);
    int line = 0;
    for (; !fin.eof(); line++) {
        fin.getline(map[line], 1024);
        int len = strlen(map[line]);
        for (int j = 0; j < len; j += 1) {
            switch (map[line][j]) {
            case 'S':
                // starting point
                playerX = line;
                playerY = j;
                break;

                // more cases for more levels
            }

        }
    }
    mapWidth = (int)strlen(map[0]);
    mapHeight = line;
    memcpy(originalMap, map, sizeof(map));
    originalMap[playerX][playerY] = ' ';// keep map clean

    cout << "Read map from " << filename << " of size " << mapWidth << "x" << mapHeight << '\n';
}


vector<Obstacle> obstacles;
int score = 0;
void GameOverScreen(Obstacle& obstacle) {
    UpdateMap();
    PrintMap();
    fout << "Game ended because of a crash with " << obstacle << " !\nFinal score : " << score;
}

#define IS_VALID(x,y)  map[x][y] == ' '
void HandlePlayerInput() {
    int decision = playerMove();
    if (decision & PLAYER_HORN) {
        fout << "\ntiit tiit :)\n";
    }
    if (decision & PLAYER_MOVE_DOWN && IS_VALID(playerX + 1, playerY) && IS_VALID(playerX + 2, playerY)) {
        playerX+= 2;
    }
    if (decision & PLAYER_MOVE_UP && IS_VALID(playerX - 1, playerY)) {
        playerX--;
    }
    if (decision & PLAYER_MOVE_RIGHT && IS_VALID(playerX, playerY + 1)) {
        playerY++;
    }
    if (decision & PLAYER_MOVE_LEFT && IS_VALID(playerX, playerY - 1)) {
        playerY--;
    }

}
void GameLoop() {
    for (;score < 1500; score++) {
        PrintMap();
        HandlePlayerInput();




        // apar mai multe obstacole pe masura ce scorul se mareste
        // de observat e ca sonia merge constant cu 50km/h, limita legala; in schimb, obstacolele si gaurile de pe strada avanseaza cu o viteza ce accelereaza constant spre masina soniei
        // si de aia apar mai multe 

        int obstaclesToSpawn = 1 + rand() % (score / SCORE_DIFFICULTY_INCREASE_THRESHOLD + 1);
        for (int i = 0; i < obstaclesToSpawn; i += 1) {
            obstacles.push_back(Obstacle(0, 1 + rand() % (mapWidth - 2)));
        }

        for (Obstacle& obstacle : obstacles) {
            if (obstacle.Crash()) {
                // game over ? 
                GameOverScreen(obstacle);
                return;
            }
            obstacle.Advance();

            if (obstacle.Crash()) {
                // what about now, game over ?  
                GameOverScreen(obstacle);
                return;
            }
        }
        std::remove_if(obstacles.begin(), obstacles.end(), [](Obstacle& it) { return it.CanDestroy(); }), obstacles.end();


        UpdateMap();
    }
}

#define SEPARATOR "\n--------------------\n"
void PrintMap() {
    fout << SEPARATOR;
    for (int i = 0; i < mapHeight; i += 1) {
        for (int j = 0; j < mapWidth; j += 1) {
            fout << map[i][j];
        }
        fout << "\n";
    }
    fout << "score : " << score << "\n";
    fout << SEPARATOR;
}
void UpdateMap() {

    memcpy(map, originalMap, sizeof(originalMap));
    map[playerX][playerY] = 'S';
    for (Obstacle& obstacle : obstacles) {
        map[obstacle.x][obstacle.y] = 'O';
    }
}
void Level1() {
    ReadMap("Level1.in");
}
