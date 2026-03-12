#include "board.h"
#include <graphics.h>

int playerColor = 1;

void initBoard()
{
	// 清空棋盘数组
	for (int i = 0; i < 9; i++)
	{
		board[i] = 0;
	}

	// 初始化图形窗口
	initgraph(550, 550);

	// 清空绘图区域（包括已绘制的棋子）
	setbkcolor(WHITE);
	cleardevice();
}

void drawBoard()
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	
	for (int i = 1; i < 3; i++)
	{
		line(50, 50 + i * 150, 500, 50 + i * 150);
		line(50 + i * 150, 50, 50 + i * 150, 500);
	}
}

void drawPiece(int pos, int Color)
{
	int row = pos / 3;
	int col = pos % 3;
	int centerX = 50 + col * 150 + 75;
	int centerY = 50 + row * 150 + 75;
	
	if (Color == 1)
	{
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 4);
		line(centerX - 50, centerY - 50, centerX + 50, centerY + 50);
		line(centerX + 50, centerY - 50, centerX - 50, centerY + 50);
	}
	else if (Color == 2)
	{
		setlinecolor(BLUE);
		setlinestyle(PS_SOLID, 4);
		circle(centerX, centerY, 50);
	}
}

int checkWin()
{
	const int win[8][3] = {
		{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}
	};
	vector<int> vec = getAvailble();
	if (vec.size() == 0)
	{
		return 0;
	}
	for (int i = 0; i < 8; i++)
	{
		if (board[win[i][0]] != 0 && board[win[i][0]] == board[win[i][1]] && board[win[i][1]] == board[win[i][2]])
		{		
				return 1;
		
		}
	}
	return -1;
}
vector<int> getAvailble()
{
	vector<int> vec;
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == 0)
		{
			vec.push_back(i);
		}
	}
	return vec;
}
void closeBoard()
{
	closegraph();
}
