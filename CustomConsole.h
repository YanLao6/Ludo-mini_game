#pragma once
#include <windows.h>
#include <random>
#include <thread>
#include <chrono>

using namespace std;

//设置光标位置函数
void setCursorPosition(int x, int y);

//设置控制台大小函数
void setConsoleSize(int width, int height);

//设置文本颜色函数
void setTextColor(WORD color);

//设置光标显示隐藏
void setCursorVisibility(bool visible);

//关闭控制台
void closeConsole();

//获取随机数
int getRandom(int min, int max);

//播放声音文件
void PlaySoundFile(const char* soundFile);
