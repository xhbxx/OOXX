#include"ai.h"
#include"board.h"
class ai
{
	int minmax(int color,int depth)
	{
		int alpha = INT_MIN;
		int beta = INT_MAX;
		int val = 0;
		if (color == aiColor)
		{
			val = INT_MIN;
		}
		else
		{
			val = INT_MAX;
		};
		for (int i = 0; i < 3, i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == )
				{
					continue;
				}
				if (color == aiColor)
				{
					val = max(val, minmax(3 - color,depth-1));
				}
				else
				{
					val=min(val,minmax(3-color,depth-1))
				}
				
			}
		}
	}
private:
	int aiColor;

};
