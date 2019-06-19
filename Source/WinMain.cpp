#pragma warning(disable:4996)

#include <Windows.h>
#include <stdio.h>

extern void serial_port_list(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	HWND hwnd;

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    serial_port_list();

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
