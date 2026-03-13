#include "board.h"

// 当前玩家颜色（用于人机对弈时）
int playerColor = 1;
 
// 初始化棋盘 - 清空所有格子并重绘图形
void initBoard()
{
	// 将棋盘所有格子重置为0（空）
	for (int i = 0; i < 9; i++)
	{
		board[i] = 0;
	}	

	// 设置背景为白色
	setbkcolor(WHITE);
	// 清空图形窗口
	cleardevice();
}

// 绘制井字棋棋盘 - 3x3网格
void drawBoard()
{
	// 设置线条颜色为黑色
	setlinecolor(BLACK);
	// 设置线条样式为实线，宽度为3像素
	setlinestyle(PS_SOLID, 3);
	
	// 绘制2条水平线和2条竖直线，形成3x3网格
	// 每个格子大小为150x150像素，起始位置为(50,50)
	for (int i = 1; i < 3; i++)
	{
		// 绘制水平线
		line(50, 50 + i * 150, 500, 50 + i * 150);
		// 绘制竖直线
		line(50 + i * 150, 50, 50 + i * 150, 500);
	}
}

// 在指定位置绘制棋子
// pos: 棋盘位置(0-8)，Color: 玩家颜色(1=红X, 2=蓝O)
void drawPiece(int pos, int Color)
{
	// 根据位置计算行列
	int row = pos / 3;
	int col = pos % 3;
	
	// 计算格子中心坐标
	// 每个格子150x150，中心偏移75像素
	int centerX = 50 + col * 150 + 75;
	int centerY = 50 + row * 150 + 75;
	
	if (Color == 1)
	{
		// AI1或玩家1：绘制红色X
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 4);
		// 绘制两条对角线
		line(centerX - 50, centerY - 50, centerX + 50, centerY + 50);
		line(centerX + 50, centerY - 50, centerX - 50, centerY + 50);
	}
	else if (Color == 2)
	{
		// AI2或玩家2：绘制蓝色圆圈O
		setlinecolor(BLUE);
		setlinestyle(PS_SOLID, 4);
		circle(centerX, centerY, 50);
	}
}

// 检查游戏是否结束
// 返回值：1=有玩家赢，0=平局，-1=游戏继续
int checkWin()
{
	// 所有可能的获胜组合（8种）
	const int win[8][3] = {
		{0,1,2},  // 第一行
		{3,4,5},  // 第二行
		{6,7,8},  // 第三行
		{0,3,6},  // 第一列
		{1,4,7},  // 第二列
		{2,5,8},  // 第三列
		{0,4,8},  // 主对角线
		{2,4,6}   // 副对角线
	};
	
	// 获取当前可用位置
	vector<int> vec = getAvailble();	
	
	// 检查是否有玩家获胜
	for (int i = 0; i < 8; i++)
	{
		// 如果三个位置都被同一玩家占据，则该玩家获胜
		if (board[win[i][0]] != 0 && 
		    board[win[i][0]] == board[win[i][1]] && 
		    board[win[i][1]] == board[win[i][2]])
		{		
			return 1;	
		}
	}
	
	// 如果没有可用位置且没有人赢，则平局
	if (vec.size() == 0)
	{
		return 0;
	}
	
	// 游戏继续
	return -1;
}

// 获取当前所有可用的下棋位置
vector<int> getAvailble()
{
	vector<int> vec;
	// 遍历棋盘，找出所有空位（值为0的位置）
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == 0)
		{
			vec.push_back(i);
		}
	}
	return vec;
}

// 关闭图形窗口
void closeBoard()
{
	closegraph();
}
