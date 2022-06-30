#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;



#define RED 20
#define STUP 40


int Stupac[] = { 0, 1, 0, -1 };
int Redak[] = { -1, 0, 1, 0 };

void labirint(char M[][STUP])
{
    for (unsigned i = 0; i < RED; i++)
    {
        for (unsigned j = 0; j < STUP; j++)
        {
            cout << M[i][j];
        }
        cout << endl;
    }
}

class Minotaur {
public:
    int stup;
    int red;
    int udaljenost;
    Minotaur(int x, int y, int w)
        : red(x), stup(y), udaljenost(w)
    {
    }
};

int minudaljenost(char M[RED][STUP], int redA, int stupacA, int redB, int stupacB)
{
    Minotaur source(0, 0, 0);

    bool bio[RED][STUP];
    for (int i = 0; i < RED; i++) {
        for (int j = 0; j < STUP; j++)
        {


            bio[i][j] = false;


            if (M[i][j] == 'A')
            {
                source.red = i;
                source.stup = j;
            }
        }
    }


    queue<Minotaur> q;
    q.push(source);
    bio[source.red][source.stup] = true;
    while (!q.empty()) {
        Minotaur p = q.front();
        q.pop();


        if (M[p.red][p.stup] == 'B')
            return p.udaljenost;


        if (p.red - 1 >= 0 &&
            bio[p.red - 1][p.stup] == false) {
            q.push(Minotaur(p.red - 1, p.stup, p.udaljenost + 1));
            bio[p.red - 1][p.stup] = true;

        }

        if (p.red + 1 < RED &&
            bio[p.red + 1][p.stup] == false) {
            q.push(Minotaur(p.red + 1, p.stup, p.udaljenost + 1));
            bio[p.red + 1][p.stup] = true;

        }


        if (p.stup - 1 >= 0 &&
            bio[p.red][p.stup - 1] == false) {
            q.push(Minotaur(p.red, p.stup - 1, p.udaljenost + 1));
            bio[p.red][p.stup - 1] = true;

        }


        if (p.stup + 1 < STUP &&
            bio[p.red][p.stup + 1] == false) {
            q.push(Minotaur(p.red, p.stup + 1, p.udaljenost + 1));
            bio[p.red][p.stup + 1] = true;
        }

        M[redA - 1][stupacA - 1] = 'A';
        M[redB - 1][stupacB - 1] = 'B';
        M[p.red][p.stup] = '*';
        labirint(M);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
    }
    return -1;
}

void input(int& redA, int& stupacA, int& redB, int& stupacB)
{
    cout << "A koordinata reda(1 - 20): ";
    cin >> redA;
    cout << "A koordinata stupca (1 - 40): ";
    cin >> stupacA;

    cout << "B koordinata reda(1 - 20): ";
    cin >> redB;
    cout << "B koordinata stupca (1 - 40): ";
    cin >> stupacB;
}


int main()
{
    int redA, stupacA, redB, stupacB;
    input(redA, stupacA, redB, stupacB);

    char M[RED][STUP];
    for (unsigned i = 0; i < RED; i++)
    {
        for (unsigned j = 0; j < STUP; j++)
        {
            M[i][j] = '-';
        }
    }

    M[redA - 1][stupacA - 1] = 'A';
    M[redB - 1][stupacB - 1] = 'B';


    cout << "Najkraci put je: " << minudaljenost(M, redA, stupacA, redB, stupacB) << endl;
    labirint(M);

    return 0;
}