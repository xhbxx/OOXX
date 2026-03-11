#include"board.h"

int board[9] = {0};

int main()
{
	initBoard();
	drawBoard();
	system("pause");
	closeBoard();
	return 0;
}
