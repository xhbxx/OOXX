#include"board.h"
#include"ai.h"
int board[9] = {0};

//int main()
//{	
//	initgraph(550, 550);
//	//储存下棋之前的棋盘
//	int state[9] = { 0 };	
//	bool isWin = false;
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
//	ai* curPlayer=&agent1;
//	ai* nextPlayer=&agent2;
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
//		isWin = false;
//		memset(state ,0, sizeof(state));
//		while (!isWin)
//		{	
//			memcpy(state,board, sizeof(board));
//			int pos= curPlayer->move();
//			drawPiece(pos, curPlayer->aiColor);
//			int win = checkWin();
//			if (win==1)
//			{	 
//				isWin = true;
//				curPlayer->value[curPlayer->convertBoard(board)] = 1;
//				nextPlayer->value[nextPlayer->convertBoard(board)] = -1;
//				double error = -1.0 - nextPlayer->value[nextPlayer->stored_OutCome];
//				nextPlayer->value[nextPlayer->stored_OutCome] += nextPlayer->alpha * error;
//				if (curPlayer->aiColor == 1)
//				{
//					one++;
//				}
//				else { two++; };
//			}
//			else if(win==0)
//			{
//				isWin = true;
//				/*curPlayer->value[curPlayer->convertBoard(board)] = 0;
//				nextPlayer->value[nextPlayer->convertBoard(state)] = 0;*/
//				neither++;
//			}
//			temp = curPlayer;
//			curPlayer = nextPlayer;
//			nextPlayer = temp;
//		}
//		
//		if (i == n)
//		{
//			cout << i << " ";
//			cout << "agent1胜利:" << one << endl;
//			cout << "agent2胜利：" << two << endl;
//			cout << "平局" << neither << endl;
//			n += 5000;
//		
//		}
//		if (i ==  50000)
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
//	//saveValueTable(agent1.value, "value1.bin");
//	//saveValueTable(agent2.value, "value2.bin");
//	system("pause");
//	return 0;
//}

int main()
{
	initgraph(550, 550);
	initBoard();
	drawBoard();
	ai agent(2);
	agent.Epsilon = 0;
	int a= 0;
	bool isWin = false;
	int win = 0;
	loadValueTable(agent.value, "value2.bin");
	while (!isWin) {
		a = playerMove();
		drawPiece(a, 1);
		board[a] = 1;
		win = checkWin();
		if (win == 1 || win == 2) isWin = true;
		a = agent.move();
		win = checkWin();
		if (win == 1 || win == 2) isWin = true;
		drawPiece(a, 2);
	}
	system("pause");
}
