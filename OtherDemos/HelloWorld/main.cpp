#include <stdint.h>
#include <stdio.h>

#include <Windows.h>

#include "debug.h"

#pragma warning(disable:4996)

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	MSG msg;

	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	TRACE("Hello World\n");

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}