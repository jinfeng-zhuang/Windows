#include "common.h"


extern int FrameGenerator(void *arg);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
    HWND hwnd;
    HANDLE hThread;

#if 1
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    //freopen("log.txt", "w", stdout);
#endif

#if 0
    CustomWindowClassesInit(hInstance);

    hThread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)FrameGenerator, NULL, 0, NULL);
    if (NULL == hThread)
        return -1;

#if 0
    HMENU hRoot;
    HMENU hPop1;

    hRoot = CreateMenu();
    hPop1 = CreatePopupMenu();
    AppendMenu(hRoot, MF_POPUP, (UINT_PTR)hPop1, L"File");
    AppendMenu(hPop1, MF_POPUP, (UINT_PTR)1, L"1");
    AppendMenu(hPop1, MF_POPUP, (UINT_PTR)2, L"2");
#endif

    hwnd = CreateWindowEx(
        0, // dwExStyle
        TEXT("Game2Board"),
        TEXT("Demo"), // Title
#if 0
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
#else
        WS_OVERLAPPEDWINDOW,
#endif
        0, 0, 800, 600,
        NULL, // hWndParent
#if 0
        hRoot, // hMenu
#else
        NULL,
#endif
        hInstance,
        NULL);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    SendMessage(hwnd, WM_USER, 0, 50);
    SendMessage(hwnd, WM_USER+1, 10, 5);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)(msg.wParam);
#endif
    serial_port_list();
}
