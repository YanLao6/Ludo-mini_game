#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <cstddef>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <windows.h>
#include "CustomConsole.h"
using namespace std;

//游戏界面枚举
enum E_gamescene
{
	begin,
	game,
	last
};

//格子枚举
enum E_grid
{
	usual,
	bomb,
	pause,
	random
};

//玩家类型枚举
enum E_player
{
	player,
	computer
};

//玩家的移动方向
enum E_direction
{
	right,
	left,
	down,
	up
};

//格子结构体
struct Grid
{
	E_grid type;
	int x;
	int y;
	Grid(E_grid type, int x, int y) : type(type), x(x), y(y) {}

	//绘制格子
	void drawGrid()
	{
		setTextColor(7);
		setCursorPosition(x, y);
		if (type == usual)
		{
			cout << "□";
		}
		else if (type == bomb)
		{
			setTextColor(12);
			cout << "○";
		}
		else if (type == pause)
		{
			setTextColor(14);
			cout << "▽";
		}
		else if (type == random)
		{
			setTextColor(10);
			cout << "△";
		}
	}
	Grid() {}
};

//玩家结构体
struct Player
{
	E_player type;
	E_direction direction;
	bool ifPause;
	int x;
	int y;
	Player(E_player type, int x, int y,
		E_direction direction, bool ifPause) :
		type(type), x(x), y(y), direction(direction),
		ifPause(ifPause)
	{
	}

	//绘制玩家
	void drawPlayer()
	{
		setTextColor(4);
		setCursorPosition(x, y);
		if (type == E_player::player)
		{
			cout << "○";
		}
		else if (type == E_player::computer)
		{
			cout << "●";
		}
		setTextColor(7);
	}
};

//全局变量
extern E_gamescene scene;
extern Grid grid[150];
extern Player players[2];//生成玩家
extern bool whoGo;
extern int num;
extern short dice;
extern bool ifGameOver;

//开始界面
void start();

//清空控制台代码
void clearConsole();

//游戏主界面
void MainScene();

//绘制地图
void DrawMap();

//绘制游戏路径
void DrawPath();

//生成格子
void GenerateGrid();

//玩家前进
void MovePlayer(Player& player);

//玩家后退
void BackPlayer(Player& player);

//绘制玩家的位置
void DrawPlayer();

//输出陷阱信息
void trapsInformation(Player& player, E_grid& type);

//踩到陷阱
void CheckTraps(Player& player);

//暂停时间
void pauseForSeconds(int seconds);

//玩家前进路径
void playerPath();

//结束界面
void EndScene();
