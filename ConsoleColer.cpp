#include "CustomConsole.h"

//设置光标位置
void setCursorPosition(int x, int y)
{
	// 获取当前的标准输出句柄
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 设置光标位置的坐标
	COORD cursorPosition;
	cursorPosition.X = x;  // 横坐标（列）
	cursorPosition.Y = y;  // 纵坐标（行）

	// 调用 Windows API 函数设置光标位置
	SetConsoleCursorPosition(hConsole, cursorPosition);
}

//设置控制台大小
void setConsoleSize(int width, int height)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 设置控制台屏幕缓冲区大小
	COORD bufferSize;
	bufferSize.X = width + 2;
	bufferSize.Y = height + 1;
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	// 设置控制台窗口大小
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width;
	windowSize.Bottom = height;
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

//设置文本颜色
void setTextColor(WORD color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

//设置光标显隐
void setCursorVisibility(bool visible)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	// 获取当前光标信息
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = visible;  // 设置光标是否可见
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

//关闭控制台
void closeConsole()
{
	HWND hConsole = GetConsoleWindow();  // 获取控制台窗口句柄
	if (hConsole != NULL)
	{
		PostMessage(hConsole, WM_CLOSE, 0, 0);  // 发送关闭消息
	}
}

int getRandom(int min, int max)
{
	// 创建随机数生成器
	random_device rd;  // 获得随机数种子
	mt19937 gen(rd()); // 使用 Mersenne Twister 生成器
	uniform_int_distribution<> dis(min, max); // 定义均匀分布 [0, 99]

	// 生成一个随机数
	int randomNumber = dis(gen);
	return randomNumber;
}