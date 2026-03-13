#include"board.h"
#include"ai.h"

// 全局棋盘数组
int board[9] = {0};

int main()
{	
	// 初始化图形窗口（550x550像素）
	initgraph(550, 550);
	
	// 储存下棋之前的棋盘状态（用于TD学习）
	int state[9] = { 0 };	
	
	// 标记游戏是否结束
	bool isWin = false;
	
	// 记录当前下棋位置
	int pos = 0;
	
	// 统计两个AI的胜场数
	int one = 0;   // AI1胜场
	int two = 0;   // AI2胜场
	int neither = 0; // 平局数

	// 创建两个AI智能体
	// AI1使用颜色1（红X），AI2使用颜色2（蓝O）
	ai agent1(1);
	ai agent2(2);
	
	// 从保存的文件加载已训练的价值表
	loadValueTable(agent1.value, "value.bin");
	
	// 设置探索率
	// agent1：初始探索率0.3（较多探索）
	// agent2：初始探索率1.0（完全随机）
	agent1.Epsilon = 0.3;
	agent2.Epsilon = 1;
	
	// 记录当前玩家和下一个玩家
	ai* curPlayer = &agent1;
	ai* nextPlayer = &agent2;
	
	// 用于交换玩家的临时指针
	ai* temp = &agent1;
	
	// 训练参数
	const int TOTAL_GAMES = 1000000;  // 总训练局数
	const int PRINT_INTERVAL = 50000; // 每50000局打印一次统计信息
	
	// 主训练循环
	for (int i = 0; i < TOTAL_GAMES; i++)
	{	
		// 初始化新的一局游戏
		initBoard();
		drawBoard();		
		
		// 重置本局的统计变量
		int winner1 = 0;
		int winner2 = 0;
		int draw = 0;
		isWin = false;
		memset(state, 0, sizeof(state));
		
		// 重置两个AI的状态
		agent1.reset();
		agent2.reset();
		
		// 单局游戏循环 - 直到游戏结束
		while (!isWin)
		{	
			// 保存下棋前的棋盘状态
			memcpy(state, board, sizeof(board));
			
			// 当前玩家执行下棋动作
			int pos = curPlayer->move();
			
			// 在图形窗口绘制棋子
			drawPiece(pos, curPlayer->aiColor);
			
			// 检查游戏是否结束
			// 返回值：1=有人赢，0=平局，-1=游戏继续
			int win = checkWin();
			
			if (win == 1)
			{	 
				// 有玩家获胜
				isWin = true;
				
				// 更新价值表：赢家获得+1，输家获得-1
				curPlayer->value[curPlayer->convertBoard(board)] = 1;
				nextPlayer->value[nextPlayer->convertBoard(state)] = -1;
				
				// 统计胜场
				if (curPlayer->aiColor == 1)
				{
					one++;
				}
				else 
				{ 
					two++; 
				}
			}
			else if (win == 0)
			{
				// 平局
				isWin = true;
				
				// 更新价值表：双方都获得0
				curPlayer->value[curPlayer->convertBoard(board)] = 0;
				nextPlayer->value[nextPlayer->convertBoard(state)] = 0;
				
				// 统计平局
				neither++;
			}
			
			// 交换玩家（轮流下棋）
			temp = curPlayer;
			curPlayer = nextPlayer;
			nextPlayer = temp;
		}
		
		// 定期打印训练进度和统计信息
		if ((i + 1) % PRINT_INTERVAL == 0)
		{
			cout << "第 " << (i + 1) << " 局 | ";
			cout << "AI1胜利: " << one << " | ";
			cout << "AI2胜利: " << two << " | ";
			cout << "平局: " << neither << " | ";
			cout << "AI1胜率: " << (double)one / (i + 1) * 100 << "%" << endl;
			
			// 在100000局时降低探索率，进入利用阶段
			if (i + 1 == 100000)
			{
				agent1.Epsilon = 0.1;  // 降低AI1的探索率
				cout << ">>> 已完成100000局，降低AI1探索率至0.1" << endl;
			}
		}
	}
	
	// 训练完成，打印最终统计
	cout << "\n========== 训练完成 ==========" << endl;
	cout << "总局数: " << TOTAL_GAMES << endl;
	cout << "AI1胜利: " << one << " (" << (double)one / TOTAL_GAMES * 100 << "%)" << endl;
	cout << "AI2胜利: " << two << " (" << (double)two / TOTAL_GAMES * 100 << "%)" << endl;
	cout << "平局: " << neither << " (" << (double)neither / TOTAL_GAMES * 100 << "%)" << endl;
	cout << "=============================" << endl;
	
	// 保存训练后的价值表到文件
	saveValueTable(agent1.value, "value.bin");
	cout << "价值表已保存到 value.bin" << endl;
	
	system("pause");
	return 0;
}
