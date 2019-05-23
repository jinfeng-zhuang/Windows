#include "api.h"

#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	HWND hwnd;

	g_instance = hInstance;
	
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	MyWindowRegister();

	hwnd = MyWindowCreate(0, 0, 800, 600);
	if (hwnd == NULL) {
		printf("window_create failed");
		return false;
	}

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
