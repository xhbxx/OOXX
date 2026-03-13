#pragma once
#include "board.h"

class ai 
{
public:
	ai(int color);
	// 重置储存的outcome
	void reset();
	int move();
	// 价值数组 - 存储所有可能棋盘状态的价值评估
	vector<double> value;
	int aiColor;
	// 探索率(Epsilon) - 控制随机探索vs贪心利用的比例
	double Epsilon;
	int minmax(int Color, int depth);
	// 将棋盘状态转化为价值表索引 
	int convertBoard(int Board[9]);
	void revertBoard(int index, int board[9]);
	// 生成0到n之间的随机数 
	int random(int n);
	// 学习率(Alpha) - 控制价值更新的步长
	double alpha;
	// 记录自己走后的局面对应的价值表索引
	int stored_OutCome;
	// 记录本局走过的所有状态，用于游戏结束时的批量更新
	vector<int> episode_states;
	// 游戏结束时的奖励值
	double final_reward;
private:
	// 静态随机数生成器 - 避免重复初始化
	static std::mt19937 rng;
};
// 保存价值表到二进制文件
void saveValueTable(const std::vector<double>& table, const std::string& filename);
// 从二进制文件加载价值表
void loadValueTable(std::vector<double>& table, const std::string& filename);
