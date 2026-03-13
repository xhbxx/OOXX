#include"ai.h"


 
ai::ai(int Color)
	:aiColor(Color)
	,value(19683,0.5)
	,Epsilon(0.1)
	,alpha(0.1)
	,stored_OutCome(0)
{} 

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
					val = max(val, minmax(3 - Color,depth-1));
				}
				else
				{
					val = min(val, minmax(3 - Color, depth - 1));
				}			
		}
		return 0;
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
	if (random(9)/10.0 < this->Epsilon)
	{	
		//随机的下棋点 
		bestPoint = random(n-1);
		board[availble[bestPoint]] = this->aiColor;
		temp = value[convertBoard(board)];
	}
	else 
	{	//临时记录下一步每个棋局的价值 
		vector<double> tempValue(9,0);
		//假想下棋，记录棋局分数
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
void saveValueTable(const std::vector<double>& table, const std::string& filename) {
	// std::ios::binary 告诉 C++：直接传数据，不要做任何字符转换
	std::ofstream outFile(filename, std::ios::out | std::ios::binary);

	if (outFile.is_open()) {
		// 参数 1：数据的首地址（转成 char 指针）
		// 参数 2：总长度（元素个数 * 每个 double 的大小）
		outFile.write(reinterpret_cast<const char*>(table.data()), table.size() * sizeof(double));
		outFile.close();
	}
}
void loadValueTable(std::vector<double>& table, const std::string& filename) {
	std::ifstream inFile(filename, std::ios::in | std::ios::binary);

	if (inFile.is_open()) {
		inFile.read(reinterpret_cast<char*>(table.data()), table.size() * sizeof(double));
		inFile.close();
	}
}
