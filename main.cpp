#include"board.h"
#include"ai.h"

// 全局棋盘数组
int board[9] = {0};

// 是否启用图形绘制（false=无头训练模式，速度快）
const bool ENABLE_GRAPHICS = false;

int main()
{	
	// 仅在启用图形时初始化窗口
	if (ENABLE_GRAPHICS)
	{
		initgraph(550, 550);
	}
	
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
	// agent1：初始探索率0.5（50%概率随机探索）
	// agent2：初始探索率1.0（完全随机，不学习）
	agent1.Epsilon = 0.5;
	agent2.Epsilon = 1.0;
	
	// 记录当前玩家和下一个玩家
	ai* curPlayer = &agent1;
	ai* nextPlayer = &agent2;
	
	// 用于交换玩家的临时指针
	ai* temp = nullptr;
	
	// 训练参数
	const int TOTAL_GAMES = 50000000;  // 总训练局数（5000万）
	const int PRINT_INTERVAL = 500000; // 每50万局打印一次统计信息
	
	// 主训练循环
	for (int i = 0; i < TOTAL_GAMES; i++)
	{	
		// 初始化新的一局游戏
		initBoard();
		
		if (ENABLE_GRAPHICS)
		{
			drawBoard();
		}
		
		// 标记游戏是否结束
		bool isWin = false;
		
		// 储存下棋之前的棋盘状态（用于TD学习）
		int state[9] = { 0 };
		
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
			
			// 在图形窗口绘制棋子（仅在启用图形时）
			if (ENABLE_GRAPHICS)
			{
				drawPiece(pos, curPlayer->aiColor);
			}
			
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
			int games_played = i + 1;
			double ai1_win_rate = (double)one / games_played * 100;
			double ai2_win_rate = (double)two / games_played * 100;
			double draw_rate = (double)neither / games_played * 100;
			
			cout << "第 " << games_played << " 局 | ";
			cout << "AI1胜: " << one << " (" << ai1_win_rate << "%) | ";
			cout << "AI2胜: " << two << " (" << ai2_win_rate << "%) | ";
			cout << "平局: " << neither << " (" << draw_rate << "%) | ";
			cout << "Epsilon: " << agent1.Epsilon << endl;
			
			// 平滑的Epsilon衰减策略
			// 从0.5逐渐衰减到0.05，使用指数衰减
			if (agent1.Epsilon > 0.05)
			{
				agent1.Epsilon *= 0.9999;  // 每局衰减0.01%
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
	
	if (ENABLE_GRAPHICS)
	{
		closeBoard();
	}
	
	system("pause");
	return 0;
}
