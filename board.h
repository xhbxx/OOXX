#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<random>
#include<fstream>
#include<vector>
#include <graphics.h>
using namespace std;
 
extern int board[9];
extern int playerColor;

void initBoard();
void drawBoard();
void drawPiece(int pos, int Color);
int playerMove();
void closeBoard();
vector<int> getAvailble();
int checkWin();