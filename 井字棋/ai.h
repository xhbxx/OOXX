#pragma once
#include "board.h"

class ai 
{
public:
	ai(int color);
	int aiColor;
	//价值数组 
	vector<double> value;
	//随机率 
	double Epsilon;
	//学习率 
	double alpha;
	//记录自己走后的局面 
	int stored_OutCome;
	//重置储存的outcome 
	void reset();
	int move();
	//一般计算价值 
	int minmax(int Color, int depth,int alpha,int beta);
	int evaluate();
	//转化棋盘  
	int convertBoard(int Board[9]);
	void revertBoard(int index,int board[9]);
	//生成随机数  
	int random(int n);	
	int minmaxMove(int depth);
}; 
//获取价值表  
void saveValueTable(const vector<double>& table, const string& filename);
void loadValueTable(vector<double>& table, const string& filename);
	