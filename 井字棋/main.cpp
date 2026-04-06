#include"board.h"
#include"ai.h"
int board[9] = {0};

//强化学习版本
//int main()
//{	
//	initgraph(550, 550);
//	//储存下棋之前的棋盘
//	int state[9] = { 0 };	
//	bool iswin = false;
//	//记录当前下棋位置
//	int pos = 0;
//	//记录谁赢了
//	int one = 0;
//	int two = 0;
//	int neither = 0;
//
//	ai agent1(1);
//	ai agent2(2);
//	//读取记录的价值表
//	loadValueTable(agent1.value, "value1.bin");
//	loadValueTable(agent2.value, "value2.bin");
//	agent1.Epsilon = 0.1;
//	agent2.Epsilon = 0.1;
//	//记录谁在下棋		
//	ai* curplayer=&agent1;
//	ai* nextplayer=&agent2;
//	//change
//	ai* temp = &agent1;
//	int n = 5000;
//	for (int i = 0; i <  50000; i++)
//	{	
//		initBoard();
//		drawBoard();
//		agent1.reset();
//		agent2.reset();
//		int winner1 = 0;                         
//		int winner2 = 0;
//		int draw = 0;
//		iswin = false;
//		memset(state ,0, sizeof(state));
//		while (!iswin)
//		{	
//			memcpy(state,board, sizeof(board));
//			int pos= curplayer->move();
//			drawPiece(pos, curplayer->aiColor);
//			int win = checkWin();
//			if (win==1)
//			{	 
//				iswin = true;
//				curplayer->value[curplayer->convertBoard(board)] = 1;
//				nextplayer->value[nextplayer->convertBoard(board)] = -1;
//				double error = -1.0 - nextplayer->value[nextplayer->stored_OutCome];
//				nextplayer->value[nextplayer->stored_OutCome] += nextplayer->alpha * error;
//				if (curplayer->aiColor == 1)
//				{
//					one++;
//				}
//				else { two++; };
//			}
//			else if(win==0)
//			{
//				iswin = true;
//				neither++;
//			}
//			temp = curplayer;
//			curplayer = nextplayer;
//			nextplayer = temp;
//		}
//		
//		if (i == n)
//		{
//			cout << i << " ";
//			cout << "agent1胜利:" << one << endl;
//			cout << "agent2胜利：" << two << endl;
//			cout << "平局" << neither << endl;
//			n += 500;
//		
//		}
//		if (i ==  1000)
//		{
//			one = 0;
//			two = 0;
//			neither = 0;
//			agent1.Epsilon = 0;
//			agent2.Epsilon = 0;
//			n += 5000;
//			
//		}
//		
//
//	}
//	cout << "agent1胜利:" << one << endl;
//	cout << "agent2胜利：" << two << endl;
//	cout << "平局" << neither << endl;
//	//savevaluetable(agent1.value, "value1.bin");
//	//savevaluetable(agent2.value, "value2.bin");
//	system("pause");
//	return 0;
//}

//人机博弈 1。强化学习 2.minmax
void RL()
{
	initgraph(550, 550);
	initBoard();
	drawBoard();
	ai agent(2);
	agent.Epsilon = 0;
	int a = 0;
	bool isWin = false;
	int win = 0;
	loadValueTable(agent.value, "value2.bin");
	while (!isWin) {
		a = playerMove();
		drawPiece(a, 1);
		board[a] = 1;
		win = checkWin();
		if (win == 1 || win == 0) return;
		a = agent.move();
		win = checkWin();
		if (win == 1 || win == 0) return;
		drawPiece(a, 2);
	}
};

void min1()
{
	initgraph(550, 550);
	initBoard();
	drawBoard();
	ai agent(2);
	agent.Epsilon = 0;
	int a = 0;
	bool isWin = false;
	int win = 0;
	while (!isWin) {
		a = playerMove();
		drawPiece(a, 1);
		board[a] = 1;
		win = checkWin();
		if (win == 1 || win == 0) return;

		a = agent.minmaxMove(9);
		drawPiece(a, 2);
		board[a] = 2;
		win = checkWin();
		if (win == 1 || win == 0) return;	
	}
};

int main()
{
	initgraph(550, 550);
	initBoard();
	drawBoard();
	settextcolor(BLACK);
	outtextxy(160, 260, _T("1.强化学习  2.minmax"));
	char k='a';
	bool isGameOver=false;
	while (1) {
		if (_kbhit()) {
			k = _getch();
			if (k == 'r') {
				isGameOver = true;
				initgraph(550, 550);
				initBoard();
				drawBoard();
				settextcolor(BLACK);
				outtextxy(160, 260, _T("1.强化学习  2.minmax"));
				continue;
			}
			else if (k == '1')
			{
				RL();
				isGameOver = true;
				k = '0';
			}
			else if (k == '2')
			{
				min1();
				isGameOver = true;
				k = '0';
			}
		}

		if (isGameOver) {
			settextcolor(BLACK);
			settextstyle(40, 0, _T("宋体"));
			outtextxy(180, 270, _T(" R "));
			isGameOver = false;
			continue;
		}
		
	}
	return 0;
}