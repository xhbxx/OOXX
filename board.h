#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<random>
#include<fstream>
#include<vector>
#include <graphics.h>
using namespace std;
 
// 全局棋盘数组 - 存储9个格子的状态
// 0=空，1=AI1(红X)，2=AI2(蓝O)
extern int board[9];

// 当前玩家颜色（用于人机对弈模式）
extern int playerColor;

// 初始化棋盘 - 清空所有格子并重绘图形窗口
void initBoard();

// 绘制3x3井字棋棋盘网格
void drawBoard();

// 在指定位置绘制棋子
// pos: 棋盘位置(0-8)，Color: 玩家颜色(1=红X, 2=蓝O)
void drawPiece(int pos, int Color);

// 关闭图形窗口
void closeBoard();

// 获取当前所有可用的下棋位置（空位）
vector<int> getAvailble();

// 检查游戏是否结束
// 返回值：1=有玩家赢，0=平局，-1=游戏继续
int checkWin();

