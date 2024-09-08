#include "stdafx.h"
#include "Game.h"
#include <Windows.h>

int main()
{
	Game game;

	//HWND hwnd = GetConsoleWindow();
	//ShowWindow(hwnd, SW_HIDE);

	game.run();

	return 0;
}
