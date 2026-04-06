#include"ai.h"

ai::ai(int Color)
	:aiColor(Color)
	,value(19683,0.5)
	,Epsilon(0.1)
	,alpha(0.1)
	,stored_OutCome(0)
{} 

int ai::minmax(int Color,int depth,int alpha,int beta)
{
	if (checkWin() == 1)
	{
		if (Color == playerColor)
		{
			return 100;
		}
		return -100;
	}
	if (checkWin() == 0)
	{
		return 0;
	}
	
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
		// 只在空位置下棋
		if (board[i] != 0)
		{
			continue;
		}
		
		// 模拟下棋
		board[i] = Color;
		
		if (Color == aiColor)
		{
			val = max(val, minmax(3 - Color, depth-1,alpha,beta));
			alpha = max(alpha, val);
		}
		else
		{
			val = min(val, minmax(3 - Color, depth - 1, alpha, beta));
			beta = min(val, beta);
		}
		
		// 撤销下棋
		board[i] = 0;
		
		if(alpha > beta)
		{
			break;
		}		
	}
	return val;
}

//重置存储的棋盘
void ai::reset()
{
	this->stored_OutCome = convertBoard(board);
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
void ai::revertBoard(int index,int Board[9])
{
	for(int i=8;i>=0;i--)
	{
		Board[i]=index%3;
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
	//临时记录下一步每个棋局的价值 
	vector<double> tempValue(9, 0);
	
	if (random(9)/10.0 < this->Epsilon)
	{	
		//随机的下棋点 
		bestPoint = random(n-1);
		board[availble[bestPoint]] = this->aiColor;
		temp = this->value[convertBoard(board)];
		bestPoint = availble[bestPoint];
	}
	else 
	{	//假想下棋，记录棋局分数
		for (int point : availble)
		{
			board[point] = this->aiColor;
			index = convertBoard(board);
			tempValue[point] = this->value[index];
			board[point] = 0;
		}
		//找出价值最高的下棋点
		for (int point : availble)
		{
			if (temp < tempValue[point])
			{
				temp = tempValue[point];
				bestPoint = point;
			}
		}
		board[bestPoint] = this->aiColor;
	}
	//时序差分
	double error = temp - this->value[this->stored_OutCome];
	this->value[this->stored_OutCome] += error * this->alpha;
	this->stored_OutCome = convertBoard(board);
	return bestPoint;
}

int ai::minmaxMove(int depth)
{
	int alpha = INT_MIN;
	int beta = INT_MAX;
	int val = INT_MIN;
	int oldval = INT_MIN;
	int point = 0;
	for (int i = 0; i < 9; i++)
	{
		if (board[i] != 0)
		{
			continue;
		}
		board[i] = aiColor;
		val = max(this->minmax(playerColor, 9, alpha, beta),val);
		if (val > oldval)
		{
			oldval = val;
			point = i;
		}
		board[i] = 0;
	}
	return point;
}

void saveValueTable(const vector<double>& table, const string& filename) {
	ofstream outFile(filename, ios::out | ios::binary);
	if (outFile.is_open()) {
		outFile.write(reinterpret_cast<const char*>(table.data()), table.size() * sizeof(double));
		outFile.close();
	}
}
void loadValueTable(vector<double>& table, const string& filename) {
	ifstream inFile(filename, ios::in | ios::binary);
	if (inFile.is_open()) {
		inFile.read(reinterpret_cast<char*>(table.data()), table.size() * sizeof(double));
		inFile.close();
	}
}
