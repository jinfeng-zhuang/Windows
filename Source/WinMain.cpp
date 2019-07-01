#include "common.h"

extern void serial_port_list(void);
extern void clipboard_list(void);
extern const wchar_t* GetPredefinedClipboardFormatName(UINT format);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	HWND hwnd;

    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    //freopen("log.txt", "w", stdout);

	// Custom Window Class Register
	CustomWindowClassesInit(hInstance);

	clipboard_list();

	// Custom Window Create
	hwnd = CreateWindowEx(
		0, // dwExStyle
		TEXT("HTMLBoard"),
		TEXT("Demo"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL| WS_HSCROLL,
		0, 0, 1000, 800,
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
