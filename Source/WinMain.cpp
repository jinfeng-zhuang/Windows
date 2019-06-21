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

	// Custom Window Class Register
	CustomWindowClassesInit(hInstance);

	clipboard_list();

#if 0
	// Custom Window Create
	hwnd = CreateWindowEx(
		0, // dwExStyle
		TEXT("MyButton"),
		TEXT("Demo"),
		WS_OVERLAPPEDWINDOW,
		0, 0, 1000, 800,
		NULL, // hWndParent
		NULL, // hMenu
		hInstance,
		NULL);

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
#endif

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)(msg.wParam);
}
