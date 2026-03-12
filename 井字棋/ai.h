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
	vector<double> value;
	int aiColor;
	//随机率
	double Epsilon;
private:
	int minmax(int Color, int depth);
	int revertBoard(int index);
	int random(int n);
	//学习率
	double alpha;
	//记录自己走后的局面
	int stored_OutCome;
};
void saveValueTable(const std::vector<double>& table, const std::string& filename);
