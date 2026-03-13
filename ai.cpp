#include"ai.h"

// 静态随机数生成器 - 全局共享，避免每次调用都重新初始化
std::mt19937 ai::rng(std::random_device{}());

ai::ai(int Color)
	:aiColor(Color)
	// 价值表大小为3^9=19683（每个格子3种状态：空/己方/对方）
	,value(19683, 0.5)
	// 初始探索率为0.1（10%概率随机探索）
	,Epsilon(0.1)
	// 学习率为0.1（控制TD更新的步长）
	,alpha(0.1)
	// 初始化为0（第一步没有前驱状态）
	,stored_OutCome(0)
{}

// 重置储存的结果（每局游戏开始时调用）
void ai::reset()
{
	this->stored_OutCome = 0;
}

// 生成0到n之间的随机整数（优化版：使用静态RNG）
int ai::random(int n)
{
	// 使用均匀分布生成[0, n]范围的随机数
	std::uniform_int_distribution<int> dist(0, n);
	return dist(rng);
}

// 将棋盘状态转化为价值表索引
// 原理：将3x3棋盘的9个格子看作3进制数
// 每个格子可能的值：0(空)/1(AI1)/2(AI2)
int ai::convertBoard(int Board[9])
{
	int index = 0;
	// 从左到右遍历棋盘，每个格子乘以3的幂次
	for (int i = 0; i < 9; i++)
	{
		index = index * 3 + Board[i];
	}
	return index;
}

// 将价值表索引还原为棋盘状态（convertBoard的逆操作）
void ai::revertBoard(int index, int Board[9])
{
	// 从右到左逐位提取3进制数字
	for (int i = 8; i >= 0; i--)
	{
		Board[i] = index % 3;
		index /= 3;
	}
}

// AI决策函数 - 结合ε-贪心策略和时序差分学习
int ai::move()
{	
	// 获取当前可用的下棋位置
	vector<int> availble = getAvailble();
	
	// 当前最优位置
	int bestPoint = 0;
	
	// 可用位置数量
	int n = availble.size();
	
	// 记录每个位置的价值评估
	double temp = 0.0;
	
	// ε-贪心策略：以Epsilon概率随机探索，否则选择价值最高的位置
	if (random(9) / 10.0 < this->Epsilon)
	{	
		// 随机选择一个可用位置（探索）
		bestPoint = random(n - 1);
		board[availble[bestPoint]] = this->aiColor;
	}
	else 
	{	
		// 贪心选择：评估每个可用位置的价值
		vector<double> tempValue(9, 0);
		
		// 对每个可用位置进行评估
		for (int point : availble)
		{
			// 临时下棋
			board[point] = this->aiColor;
			// 转换为价值表索引
			int index = convertBoard(board);
			// 记录该位置的价值
			tempValue[point] = this->value[index];
			// 撤销下棋
			board[point] = 0;
 		}
		
		// 找到价值最高的位置
		for (int point : availble)
		{
			if (temp < tempValue[point])
			{
				temp = tempValue[point];
				bestPoint = point;
			}
		}
		
		// 执行最优下棋
		board[bestPoint] = this->aiColor;
	}
	
	// 时序差分(TD)学习：更新前一步的价值估计
	// 公式：V(s) = V(s) + α * [V(s') - V(s)]
	double error = temp - this->value[this->stored_OutCome];
	this->value[this->stored_OutCome] += error * this->alpha;
	
	// 保存当前状态作为下一步的前驱状态
	this->stored_OutCome = convertBoard(board);
	
	return bestPoint;
}

// 保存价值表到二进制文件
void saveValueTable(const std::vector<double>& table, const std::string& filename) 
{
	// 以二进制写入模式打开文件
	std::ofstream outFile(filename, std::ios::out | std::ios::binary);

	if (outFile.is_open()) 
	{
		// 将vector的数据指针转换为char指针，写入二进制数据
		// 写入大小 = 元素个数 * 每个double的字节数
		outFile.write(reinterpret_cast<const char*>(table.data()), table.size() * sizeof(double));
		outFile.close();
	}
}

// 从二进制文件加载价值表
void loadValueTable(std::vector<double>& table, const std::string& filename) 
{
	// 以二进制读入模式打开文件
	std::ifstream inFile(filename, std::ios::in | std::ios::binary);

	if (inFile.is_open()) 
	{
		// 从二进制文件读取数据到vector
		inFile.read(reinterpret_cast<char*>(table.data()), table.size() * sizeof(double));
		inFile.close();
	}
}
