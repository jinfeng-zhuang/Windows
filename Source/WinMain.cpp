#include "common.h"

extern void serial_port_list(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	HWND hwnd;

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

	// Custom Window Class Register
	CustomWindowClassesInit(hInstance);

	// Custom Window Create
	hwnd = CreateWindowEx(
		0, // dwExStyle
		TEXT("MyButton"),
		TEXT("Demo"),
		WS_OVERLAPPEDWINDOW,
		0, 0, 400, 400,
		NULL, // hWndParent
		NULL, // hMenu
		hInstance,
		NULL);

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)(msg.wParam);
}
