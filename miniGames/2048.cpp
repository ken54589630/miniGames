﻿// 2048.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <windows.h> 
using namespace std;

int const ROW = 4;
int const COL = 4;
int game[ROW][COL] = { 0 };

//上下左右  
int const UP = 1;
int const DOWN = 2;
int const LEFT = 3;
int const RIGHT = 4;

//遊戲狀態
int const GAME_OVER = 1;
int const GAME_WIN = 2;
int const GAME_CONTINUE = 3;

enum GameNum
{
    Game_2 = 2,
    Game_4 = 4,
    Game_8 = 8,
    Game_16 = 16,
    Game_32 = 32,
    Game_64 = 64,
    Game_128 = 128,
    Game_256 = 256,
    Game_512 = 512,
    Game_1024 = 1024,
    Game_2048 = 2048,
};

void Print() {
    system("cls");
    cout << "***********   2048   ************" << endl;
    cout << "********   By Ken Kao   *********" << endl << endl;

    for (int i = 0; i < ROW; ++i) {
        cout << "---------------------------------" << endl;
        for (int j = 0; j < COL; ++j) {
            if (game[i][j] == 0)
                cout << "|   \t";
            else
                cout << "|   " << game[i][j] << "\t";
        }
        cout << "|" << endl;
    }
    cout << "---------------------------------" << endl;
}

bool CreateNumber() {
    int x = -1;
    int y = -1;
    int times = 0;
    int maxTimes = ROW * COL;
    //三分之二的機率生成2，三分之一的機率生成4  
    int whitch = rand() % 3;

    do {
        x = rand() % ROW;
        y = rand() % COL;
        ++times;
    } while (game[x][y] != 0 && times <= maxTimes);

    //若格子滿了
    if (times >= maxTimes)
        return false;
    else {
        GameNum num;
        if (whitch == 0)
            num = Game_4;
        else if(whitch)
            num = Game_2;
        game[x][y] = num;
    }
    
    return true;
}

//讀取輸入，返回上下左右
int Input() {
    //讀取上下左右四個方向鍵
    int upArrow = 0;
    int downArrow = 0;
    int leftArrow = 0;
    int rightArrow = 0;
    int direction = 0;

    while (true) {
        upArrow = GetAsyncKeyState(VK_UP);
        downArrow = GetAsyncKeyState(VK_DOWN);
        leftArrow = GetAsyncKeyState(VK_LEFT);
        rightArrow = GetAsyncKeyState(VK_RIGHT);

        if (upArrow) {
            direction = UP;
            break;
        }
        else if (downArrow) {
            direction = DOWN;
            break;
        }
        else if (leftArrow) {
            direction = LEFT;
            break;
        }
        else if (rightArrow) {
            direction = RIGHT;
            break;
        }

        Sleep(100);
    }

    return direction;
}

int Judge() {
    //Win
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (game[i][j] == 2048) {
                return GAME_WIN;
                break;
            }
        }
    }

    //橫向檢查
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL - 1; j++) {
            if (!game[i][j] || game[i][j] == game[i][j + 1]) {
                return GAME_CONTINUE;
                break;
            }
        }
    }

    //縱向檢查
    for (int j = 0; j < COL; j++) {
        for (int i = 0; i < ROW - 1; i++) {
            if (!game[i][j] || game[i][j] == game[i + 1][j]) {
                return GAME_CONTINUE;
                break;
            }
        }
    }

    return GAME_OVER;
}

void Process(int direction) {
    switch (direction) {
        case UP:
            //最上面一行不動
            for (int row = 1; row < ROW; row++) {
                for (int crow = row; crow >= 1; crow--) {
                    for (int col = 0; col < COL; col++) {
                        //上一個格子為空
                        if (game[crow - 1][col] == 0) {
                            game[crow - 1][col] = game[crow][col];
                            game[crow][col] = 0;
                        }
                        else {
                            //合併
                            if (game[crow - 1][col] == game[crow][col]) {
                                game[crow - 1][col] *= 2;
                                game[crow][col] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case DOWN:
            //最下面一行不動
            for (int row = ROW - 2; row >= 0; row--) {
                for (int crow = row; crow < ROW - 1; crow++) {
                    for (int col = 0; col < COL; col++) {
                        //上一個格子為空
                        if (game[crow + 1][col] == 0) {
                            game[crow + 1][col] = game[crow][col];
                            game[crow][col] = 0;
                        }
                        else {
                            //合併
                            if (game[crow + 1][col] == game[crow][col]) {
                                game[crow + 1][col] *= 2;
                                game[crow][col] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case LEFT:
            //最左邊一列不動
            for (int col = 1; col < COL; col++) {
                for (int ccol = col; ccol >= 1; ccol--) {
                    for (int row = 0; row < ROW; row++) {
                        //上一個格子為空
                        if (game[row][ccol - 1] == 0) {
                            game[row][ccol - 1] = game[row][ccol];
                            game[row][ccol] = 0;
                        }
                        else {
                            //合併
                            if (game[row][ccol - 1] == game[row][ccol]) {
                                game[row][ccol - 1] *= 2;
                                game[row][ccol] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case RIGHT:
            //最右邊一列不動
            for (int col = COL - 2; col >= 0; col--) {
                for (int ccol = col; ccol <= COL - 2; ccol++) {
                    for (int row = 0; row < ROW; row++) {
                        //上一個格子為空
                        if (game[row][ccol + 1] == 0) {
                            game[row][ccol + 1] = game[row][ccol];
                            game[row][ccol] = 0;
                        }
                        else {
                            //合併
                            if (game[row][ccol + 1] == game[row][ccol]) {
                                game[row][ccol + 1] *= 2;
                                game[row][ccol] = 0;
                            }
                        }
                    }
                }
            }
            break;
    }
}

int main()
{
    srand(time(0));
    CreateNumber();
    CreateNumber();
    Print();
    int direction = 0;
    int gameState = -1;
    while (true) {
        direction = Input();

        gameState = Judge();

        if (direction && gameState == GAME_CONTINUE) {
            Process(direction);
            CreateNumber();
            Print();
            Sleep(100);
        }
        else if (gameState == GAME_WIN) {
            Print();
            cout << "You win!" << endl;
            break;
        }
        else if (gameState == GAME_OVER) {
            Print();
            cout << "You lose!" << endl;
            break;
        }
    }

    return 0;
}
