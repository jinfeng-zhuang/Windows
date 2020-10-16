#pragma comment(lib, "comctl32.lib")
#pragma warning(disable:4996)

#include <Windows.h>
#include <stdio.h>

extern void WindowClassMain_Register(HINSTANCE hInstance);

#define TITLE   TEXT("RebarExample")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HWND hWnd;
    MSG msg;

#if 1
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
#endif

    WindowClassMain_Register(hInstance);

    hWnd = CreateWindowEx(
        0,
        TEXT("WindowClassMain"),
        TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
