/*
        SNAKEGAME
        *****************Programmed BY : Samip Gyawali ******************
       Controls W-Up A-Left S-Down D-Right
        
        */


#include <iostream>
#include <conio.h>
#include<fstream>
#include<sstream>
#include<string>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;

int posX, posY, headX, headY, score, width, height;
bool stopGame = false;

enum direction{StopIt, Up, Down, Right, Left};
direction chDir;

int tailX[100];
int tailY[100];
int tLength;

void initial() {
    score = 0;
    width = 100;
    height = 20;
    headX = width / 2;
    headY = height / 2;
    chDir = StopIt;
     posX = rand() % width;
     posY = rand() % height;
    
}



void input() {
    if (_kbhit()) {
        switch(_getch()) {
            case 'w':
            case KEY_UP:
                chDir = Up;
                break;
            case 'a':
            case KEY_LEFT:
                chDir = Left;
                break;
            case 's':
            case KEY_DOWN:
                chDir = Down;
                break;
            case 'd':
            case KEY_RIGHT:
                chDir = Right;
                break;
            case 'x':
                chDir = StopIt;
                break;

        }
    }
}

void gameLogic() {

    tailX[0] = headX;
    tailY[0] = headY;
    int heaXprev = tailX[0], heaYprev = tailY[0];
    int haeXXprev, haeYYprev;
    
    for (int i = 1; i <= tLength; i++) {
        haeXXprev = tailX[i];
        haeYYprev = tailY[i];
        tailX[i] = heaXprev;
        tailY[i] = heaYprev;
        heaXprev = haeXXprev;
        heaYprev = haeYYprev;
    }

    

    switch (chDir) {
    case Up:
        headY--;
        break;

    case Down:
        headY++;
        break;

    case Left:
        headX--;
        break;

    case Right:
        headX++;
        break;

    case StopIt:
        break;

   }

    if (headX < 0) {
        headX = width;
    }
    if (headX > width) {
        headX = 0;
    }

    if (headY < 0) {
        headY = height;
    }
    if (headY > height) {
        headY = 0;
    }

    if (headX == posX && headY == posY) {
        tLength++;
        score += 10;
        posX = rand() % width;
        posY = rand() % height;
    }

    for (int i = 1; i <= tLength; i++) {
        if (headX == tailX[i] && headY == tailY[i]) {
            stopGame = true;
        }
        else
        {
            stopGame = false;
        }
    }

}

void position() {
    
    system("CLS");

    for (int i = 0; i <= width; i++) {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i <= height; i++) {
       
        for (int j = 0; j <= width; j++) {
            bool print = true;
            if (j == 0 || j==width) {
                cout << "#";
            }

            else if (j == headX && i == headY) {
                cout << "O";
            }

            else if (j == posX && i == posY) {
                cout << "X";
            }

            
            else {

                for (int k = 1; k <= tLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = false;
                    }
                }
                if (print == true) {
                    cout << " ";
                }
            }
           

        }
        cout << endl;
    }
    for (int i = 0; i <= width; i++) {
        cout << "#";
    }
    cout << endl;
}


int main(){

   initial();
    while (!stopGame) {
        input();
        gameLogic();
        position();
        
        cout << endl;

        cout << "Score: " << score;
    }
    fstream MyWriteFile("scores.txt");
    string txt;
    int check;
    while (getline(MyWriteFile, txt)) {
        stringstream geek(txt);
        geek >> check;
        if (check > score) {
            cout << "\nHigh score not beaten " << "High score is: " << check;
        }
        else if (score > check) {
            cout << "New High score set";
            MyWriteFile << score;
        }
        else {
            cout << "Same high score";
        }
    }


    cout << "\n";
    cout << "Game Over";

    

    
}



