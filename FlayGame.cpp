#include "game.h"
#include "CustomConsole.h"

using namespace std;

//开始界面
void start()
{
	cout << "\n\n\n\n              欢迎来到飞行棋游戏！" << endl;
	char a = 'w';
	short b = 0;
	while (true)
	{
		switch (a)
		{
			case 'w':
			case 'W':
			{
				setTextColor(7);
				setCursorPosition(0, 0);
				cout << "\n\n\n\n              欢迎来到飞行棋游戏！" << endl;
				cout << "          (通过w和s键切换选项按q选定)" << endl;
				setCursorPosition(0, 7);
				setTextColor(4);
				cout << "\n                  开始游戏" << endl;
				setTextColor(7);
				cout << "\n                  结束游戏" << endl;
				a = _getch();
				if (a == 'q' || a == 'Q')
				{
					b = 1;
					break;
				}
				break;
			}
			case 's':
			case 'S':
			{
				setTextColor(7);
				setCursorPosition(0, 0);
				cout << "\n\n\n\n              欢迎来到飞行棋游戏！" << endl;
				cout << "          (通过w和s键切换选项按q选定)" << endl;
				setCursorPosition(0, 7);
				setTextColor(7);
				cout << "\n                  开始游戏" << endl;
				setTextColor(4);
				cout << "\n                  结束游戏" << endl;
				a = _getch();
				if (a == 'q' || a == 'Q')
				{
					b = 2;
					break;
				}
				break;
			}
			default:
			{
				continue;
			}
		}
		clearConsole();
		if (b == 0)
		{
			a = 'w';
			continue;
		}
		if (b == 1)
		{
			scene = E_gamescene::game;
			break;
		}
		if (b == 2)
		{
			closeConsole();//关闭程序
			break;
		}
	}
}

//清空控制台代码
void clearConsole()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		cerr << "无法获取控制台句柄" << endl;
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		cerr << "无法获取控制台屏幕缓冲区信息" << endl;
		return;
	}

	COORD topLeft = { 0, 0 };
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;

	// 填充空格字符
	if (!FillConsoleOutputCharacter(hConsole, ' ', length, topLeft, &written))
	{
		cerr << "无法填充控制台输出字符" << endl;
		return;
	}

	// 填充默认属性
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, length, topLeft, &written))
	{
		cerr << "无法填充控制台输出属性" << endl;
		return;
	}

	// 将光标移动到左上角
	SetConsoleCursorPosition(hConsole, topLeft);
}

//游戏主界面
void MainScene()
{
	//绘制地图
	DrawMap();

	//绘制游戏路径
	DrawPath();

	//绘制两个玩家的位置
	DrawPlayer();

	//输出骰子信息
	setCursorPosition(2, 24);
	cout << "按任意键掷骰子";
	while (true)
	{

		//玩家前进路径
		playerPath();
		if (ifGameOver == true)
		{
			setCursorPosition(2, 16);
			cout << "游戏结束！";
			scene = E_gamescene::last;
			return;
		}

		//踩到陷阱
		CheckTraps(players[whoGo]);

		//绘制两个玩家的位置
		DrawPlayer();

		setCursorPosition(2, 25);
		cout << "                                ";
		setCursorPosition(2, 25);
		if (whoGo == 0)
			cout << "你的骰子点数：" << dice << endl;
		else
			cout << "电脑玩家的骰子点数：" << dice << endl;
		Sleep(1000);
		whoGo = !whoGo;

		if (players[whoGo].ifPause == true)
		{
			players[whoGo].ifPause = false;
			whoGo = !whoGo;
		}

		//输入任意键投掷骰子
		_getch();
		dice = getRandom(1, 6);
	}
}

//绘制地图
void DrawMap()
{
	setTextColor(4);
	setCursorPosition(0, 0);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■";
	setCursorPosition(0, 30);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■";
	setCursorPosition(2, 18);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■";
	setCursorPosition(2, 19);
	setTextColor(7);
	cout << "□:普通格子，▽:暂停（一回合不动）";
	setCursorPosition(2, 20);
	cout << "○:炸弹（倒退五格）";
	setCursorPosition(2, 21);
	cout << "△:时空隧道，随机倒退，暂停，换位置";
	setCursorPosition(2, 22);
	cout << "★:玩家 ●:电脑玩家 ◎:玩家和电脑玩家重合";
	setTextColor(4);
	setCursorPosition(2, 23);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■";
	for (int i = 1; i < 30; i++)
	{
		setCursorPosition(0, i);
		cout << "■";
		setCursorPosition(48, i);
		cout << "■";
	}
	setTextColor(7);
}

//绘制游戏路径
void DrawPath()
{
	//绘制格子
	for (int i = 0; i < num; i++)
	{
		grid[i].drawGrid();
	}
}

//生成格子
void GenerateGrid()
{
	int a = 0;
	int b = 0;
	int j = 3;
	int i = 8;
	for (j = 3; j <= 13; j += 2)//y轴
	{
		for (i = 8; i <= 40; i += 2)//x轴
		{
			a = getRandom(0, 3);
			switch (a)
			{
				case 0:
				case 1:
				case 2:
				{
					grid[num++] = Grid(E_grid::usual, i, j);
					break;
				}
				case 3:
				{
					b = getRandom(0, 2);
					switch (b)
					{
						case 0:
						{
							grid[num++] = Grid(E_grid::bomb, i, j);
							break;
						}
						case 1:
						{
							grid[num++] = Grid(E_grid::pause, i, j);
							break;
						}
						case 2:
						{
							grid[num++] = Grid(E_grid::random, i, j);
							break;
						}
					}
					break;
				}
			}
		}
	}

	//补格子
	grid[num++] = Grid(E_grid::usual, 40, 4);
	grid[num++] = Grid(E_grid::usual, 8, 6);
	grid[num++] = Grid(E_grid::usual, 40, 8);
	grid[num++] = Grid(E_grid::usual, 8, 10);
	grid[num++] = Grid(E_grid::usual, 40, 12);
	grid[0].type = E_grid::usual;
	grid[1].type = E_grid::usual;
	grid[2].type = E_grid::usual;
	grid[3].type = E_grid::usual;
}

//绘制玩家的位置
void DrawPlayer()
{
	if (players[0].x == players[1].x && players[0].y == players[1].y)
	{
		setTextColor(2);
		setCursorPosition(players[0].x, players[0].y);
		cout << "◎";
		setTextColor(7);
	}
	else
	{
		setTextColor(3);
		setCursorPosition(players[0].x, players[0].y);
		cout << "★";
		setTextColor(13);
		setCursorPosition(players[1].x, players[1].y);
		cout << "●";
		setTextColor(7);
	}
}

//玩家前进
void MovePlayer(Player& player)
{
	if ((player.x == 8 && player.direction == E_direction::left)
		|| (player.x == 40 && player.direction == E_direction::right))
	{
		player.direction = E_direction::down;
		player.y++;
		return;
	}
	else if (player.direction == E_direction::right)
	{
		player.x += 2;
		return;
	}
	else if (player.direction == E_direction::left)
	{
		player.x -= 2;
		return;
	}
	else if (player.direction == E_direction::down)
	{
		player.y++;
		if (player.x == 8)
			player.direction = E_direction::right;
		else if (player.x == 40)
			player.direction = E_direction::left;
		return;
	}

}

//玩家后退
void BackPlayer(Player& player)
{
	if ((player.x == 8 && player.direction == E_direction::right)
		|| (player.x == 40 && player.direction == E_direction::left))
	{
		player.direction = E_direction::down;
		player.y--;
		return;
	}
	else if (player.direction == E_direction::right)
	{
		player.x -= 2;
		return;
	}
	else if (player.direction == E_direction::left)
	{
		player.x += 2;
		return;
	}
	else if (player.direction == E_direction::down)
	{
		player.y--;
		if (player.x == 8)
			player.direction = E_direction::left;
		else if (player.x == 40)
			player.direction = E_direction::right;
		return;
	}
}

//踩到陷阱
void CheckTraps(Player& player)
{
	for (int i = 0; i < 100; i++)
	{
		if (grid[i].x == player.x && grid[i].y == player.y)
		{
			if (grid[i].type == E_grid::bomb)
			{
				for (int j = 0; j < 5; j++)
				{
					BackPlayer(player);
				}

				//输出陷阱信息
				trapsInformation(player, grid[i].type);
				pauseForSeconds(1);
				break;
			}
			else if (grid[i].type == E_grid::pause)
			{
				player.ifPause = true;

				//输出陷阱信息
				trapsInformation(player, grid[i].type);
				pauseForSeconds(1);
				break;
			}
			else if (grid[i].type == E_grid::random)
			{
				int a = getRandom(0, 2);
				switch (a)
				{
					case 0:
					{
						for (int j = 0; j < 5; j++)
						{
							BackPlayer(player);
						}
						break;
					}
					case 1:
					{
						player.ifPause = true;
						break;
					}
					case 2:
					{
						//换位置
						int tempX = players[0].x;
						int tempY = players[0].y;
						players[0].x = players[1].x;
						players[0].y = players[1].y;
						players[1].x = tempX;
						players[1].y = tempY;
						E_direction tempDirection = players[0].direction;
						players[0].direction = players[1].direction;
						players[1].direction = tempDirection;
						break;
					}
				}

				//输出陷阱信息
				trapsInformation(player, grid[i].type);
				setCursorPosition(2, 27);
				cout << "                      ";
				setCursorPosition(2, 27);
				if (a == 0)
					cout << "是炸弹！";
				else if (a == 1)
					cout << "是暂停！";
				else
					cout << "你和人机交换了位置！";
				pauseForSeconds(1);
				break;
			}
		}
	}
}

//输出陷阱信息
void trapsInformation(Player& player, E_grid& type)
{
	setCursorPosition(2, 26);
	cout << "                                          \n                                ";
	setCursorPosition(2, 26);
	if (type == E_grid::usual)
	{
		if (player.type == E_player::player)
			cout << "你无事发生";
		else
			cout << "电脑玩家无事发生";
	}
	else if (type == E_grid::bomb)
	{
		if (player.type == E_player::player)
			cout << "你踩到了炸弹，后退五格";
		else
			cout << "电脑玩家踩到了炸弹，后退五格";
	}
	else if (type == E_grid::pause)
	{
		if (player.type == E_player::player)
			cout << "你被暂停，一回合不动";
		else
			cout << "电脑玩家被暂停，一回合不动";
	}
	else if (type == E_grid::random)
	{
		if (player.type == E_player::player)
			cout << "你进入时空隧道，随机倒退,暂停,换位置";
		else
			cout << "电脑玩家进入时空隧道，随机倒退,暂停,换位置";
	}
}

//暂停时间
void pauseForSeconds(int seconds)
{
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

//玩家前进路径
void playerPath()
{
	for (int i = 0; i < dice; i++)
	{
		//绘制地图
		DrawMap();

		//绘制游戏路径
		DrawPath();

		//输出骰子信息
		setCursorPosition(2, 24);
		cout << "按任意键掷骰子";
		setCursorPosition(2, 25);
		cout << "                                ";
		setCursorPosition(2, 25);
		if (whoGo == 0)
			cout << "你的骰子点数：" << dice << endl;
		else
			cout << "电脑玩家的骰子点数：" << dice << endl;

		//玩家前进
		if (whoGo == 0)
		{
			MovePlayer(players[0]);
		}
		else
		{
			MovePlayer(players[1]);
		}

		//绘制两个玩家的位置
		DrawPlayer();

		Sleep(200);
		if (players[whoGo].x == 8 && players[whoGo].y == 13)
		{
			ifGameOver = true;
			break;
		}
	}
}

//结束界面
void EndScene()
{
	cout << "\n\n\n\n              欢迎来到飞行棋游戏！" << endl;
	char a = 'w';
	short b = 0;
	while (true)
	{
		switch (a)
		{
			case 'w':
			case 'W':
			{
				setTextColor(7);
				setCursorPosition(0, 0);
				cout << "\n\n\n\n              欢迎来到飞行棋游戏！" << endl;
				cout << "          (通过w和s键切换选项按q选定)" << endl;
				setCursorPosition(0, 7);
				setTextColor(4);
				cout << "\n                  重新开始游戏" << endl;
				setTextColor(7);
				cout << "\n                  结束游戏" << endl;
				a = _getch();
				if (a == 'q' || a == 'Q')
				{
					b = 1;
					break;
				}
				break;
			}
			case 's':
			case 'S':
			{
				setTextColor(7);
				setCursorPosition(0, 0);
				cout << "\n\n\n\n              欢迎来到飞行棋游戏！" << endl;
				cout << "          (通过w和s键切换选项按q选定)" << endl;
				setCursorPosition(0, 7);
				setTextColor(7);
				cout << "\n                  重新开始游戏" << endl;
				setTextColor(4);
				cout << "\n                  结束游戏" << endl;
				a = _getch();
				if (a == 'q' || a == 'Q')
				{
					b = 2;
					break;
				}
				break;
			}
			default:
			{
				a = _getch();
				break;
			}
		}
		clearConsole();
		if (b == 0)
		{
			continue;
		}
		if (b == 1)
		{
			scene = E_gamescene::game;
			break;
		}
		if (b == 2)
		{
			closeConsole();//关闭程序
			break;
		}
	}
}