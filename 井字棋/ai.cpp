#include"ai.h"
#include"board.h"


ai::ai(int Color)
{
	aiColor = Color;
};
int ai::minmax(int Color,int depth)
	{
		int alpha = INT_MIN;
		int beta = INT_MAX;
		int val = 0;
		if (Color == aiColor)
		{
			val = INT_MIN;
		}
		else
		{
			val = INT_MAX;
		};
		for (int i = 0; i < 9; i++)
		{
				if (board[i] == 0)
				{
					continue;
				}
				if (Color == aiColor)
				{
					val = max(val, minmax(3 - color,depth-1));
				}
				else
				{
					val = min(val, minmax(3 - color, depth - 1));
				}			
		}
	}
//重置存储的棋盘
void ai::reset()
{
	stored_OutCome = 0;
}
//生成0到n的随机数
int ai::random(int n)
{
	mt19937 rng(random_device{}());
	uniform_int_distribution<int>dist(0, n);
	return dist(rng);
}
//把棋盘转化为索引
int ai::convertBoard(int Board[9])
{
	int index = 0;
	//三进制
	for (int i = 0; i < 9; i++)
	{
		index = index * 3 + Board[i];
	}
	return index;
}
//转化回来
int ai::revertBoard(int index)
{
	for(int i=8;i>=0;i--)
	{
		board[i]=index%3;
		index/=3;
	}
}


//下棋+更新价值
int ai::move()
{	
	//可以下棋的点
	vector<int> availble = getAvailble();
	//棋盘索引
	int index = 0;
	//有几个可以下棋的位置
	int n = availble.size();
	//最佳下棋点
	int bestPoint = 0;
	//记录tempValue最大值用于更新bestPoint
	double temp = 0.0;
	if (random(9) < Epsilon)
	{	
		//随机的下棋点
		bestPoint = random(n);
		board[bestPoint] = aiColor;
	}
	else
	{	//临时记录下一步每个棋局的价值
		vector<double> tempValue[9];
		//假想下棋，记录棋局分数
		for (int point : availble)
		{
			board[point] = aiColor;
			index = convertBoard(board);
			tempValue[point] = value[index];
			board[point] = 0;
		}
		//找出价值最高的下棋点
		for (int i = 0; i < 9; i++)
		{    
			if (temp < tempValue[i])
			{
				temp = tempValue[i];
				bestPoint = i;
			}
		}
		board[bestPoint] = aiColor;
	}
	//时序差分
	int error = temp - value[stored_OutCome];
	value[stored_OutCome] += error * Epsilon;
	stored_OutCome = convertBoard(board);
	return bestPoint;
}
