#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <ctime>
#include "resource.h"
#include <shlwapi.h> 

#pragma comment(lib, "Shlwapi.lib")
#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;

ULONG_PTR gdiplusToken;

Bitmap* BMP_background = nullptr;
Bitmap* BMP_cover = nullptr;
Bitmap* BMP_mine = nullptr;
Bitmap* BMP_one = nullptr;
Bitmap* BMP_two = nullptr;
Bitmap* BMP_three = nullptr;
Bitmap* BMP_empty = nullptr;
Bitmap* BMP_flag = nullptr;
Bitmap* BMP_counter0 = nullptr;
Bitmap* BMP_counter1 = nullptr;
Bitmap* BMP_counter2 = nullptr;
Bitmap* BMP_counter3 = nullptr;
Bitmap* BMP_counter4 = nullptr;
Bitmap* BMP_counter5 = nullptr;
Bitmap* BMP_counter6 = nullptr;
Bitmap* BMP_counter7 = nullptr;
Bitmap* BMP_counter8 = nullptr;
Bitmap* BMP_counter9 = nullptr;
Bitmap* BMP_smily = nullptr;
Bitmap* BMP_mineEnd = nullptr;
Bitmap* BMP_smilyPressed = nullptr;
Bitmap* BMP_smilyDead = nullptr;

int minesX[10];
int minesY[10];

int mouseX = 0;
int mouseY = 0;
int boxes[10][10]{};
int flagCounter = 10;
int timer = 99;
int revealedCount = 0;

bool gameOver = false;
bool smilyPressed = false;
bool clickable = true;
bool counted = false;
bool victory = false;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
Bitmap* LoadPNGResource(HINSTANCE hInstance, UINT nResourceID);
void restartGame(HWND hwnd);
