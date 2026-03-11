#pragma once
#include "board.h"

class AI
{
private:
	int aiColor; // AI的颜色 (1为X, 2为O)

public:
	// 构造函数
	AI(int color);

	// 获取AI的最佳走法
	int getBestMove();

private:
	// Minimax算法
	int minimax(int depth, bool isMaximizing);

	// 评估函数
	int evaluate();

	// 检查是否获胜
	bool checkWin(int color);

	// 检查是否平局
	bool checkDraw();
};
