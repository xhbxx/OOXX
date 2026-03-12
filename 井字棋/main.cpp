#include"board.h"
#include"ai.h"
int board[9] = {0};

int main()
{
	
	//储存下棋之前的棋盘
	int state[9] = { 0 };
	ai agent1(1);
	ai agent2(2);
	bool isWin = false;
	//记录当前下棋位置
	int pos = 0;
	for (int i = 0; i < 30000; i++)
	{
		initBoard();
		drawBoard();
		isWin = false;
		memset(state ,0, sizeof(state));
		while (!isWin)
		{	
			memcpy(board, state, sizeof(board));
			int pos=agent1.move();
			drawPiece(pos, agent1.aiColor);
			int win = checkWin();
			if (win==1)
			{
				isWin = true;
				agent1.value[agent1.convertBoard(board)] = 1;
				agent2.value[agent2.convertBoard(state)] = -1;
			}
		}
	}
	
	return 0;
}
