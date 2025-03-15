#include "game.h"
using namespace std;

E_gamescene scene = E_gamescene::begin;
Grid grid[150];
Player players[2] = { Player(E_player::player, 8, 3,
	E_direction::right,false),Player(E_player::computer,
		8, 3,E_direction::right,false) };
E_direction direction = E_direction::right;
bool whoGo = 0;
int num = 0;
short dice = 0;
bool ifGameOver = false;

int main()
{
	std::cout << "Hello, World!" << std::endl;
	//隐藏光标
	setCursorVisibility(false);

	//设置控制台大小
	setConsoleSize(50, 30);

	// 设置控制台输出代码页为UTF-8
	SetConsoleOutputCP(65001);

	// 设置控制台输入代码页为UTF-8
	SetConsoleCP(65001);

	while (true)
	{
		switch (scene)
		{
			case E_gamescene::begin:

				//开始界面
				start();
				break;
			case E_gamescene::game:

			{
				direction = E_direction::right;
				whoGo = 0;
				num = 0;
				dice = 0;
				ifGameOver = false;
				Player players[2] = { Player(E_player::player, 8, 3,E_direction::right,false),Player(E_player::computer,8, 3,E_direction::right,false) };

				//生成格子
				GenerateGrid();

				//游戏界面
				MainScene();
				break;
			}
			case E_gamescene::last:

				//结束界面
				EndScene();
				break;
		}
	}
}