#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#incdlue<random>
using namespace std;

extern int board[9];
extern int playerColor;

void initBoard();
void drawBoard();
void drawPiece(int pos, int Color);
bool playerMove();
bool checkWin();
void closeBoard();
