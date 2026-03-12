#pragma once
#include "board.h"

class ai
{
public:
	ai(int color);
	void reset();
	int move();
	int convertBoard(int Board[9]);
	//价值数组
	vector<double> value[19683];
	int aiColor;
private:
	int minmax(int Color, int depth);
	int revertBoard(int index);	
	int random(int n);
	//随机率
	int Epsilon;
	//学习率
	int alpha;
	//记录自己走后的局面
	int stored_OutCome;
};
