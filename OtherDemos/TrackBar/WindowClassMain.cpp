#include <Windows.h>
#include <stdio.h>
#include <CommCtrl.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    HDC hdc;
    PAINTSTRUCT ps;

    static HWND hTreeView = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    //printf("%s: %x %x\n", __func__, wParam, lParam);

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 100, NULL);

        InitCommonControls();

        GetClientRect(hWnd, &rc);
        hTreeView = CreateWindowEx(
            0,
            TRACKBAR_CLASS,
            0,
            WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE,
            10,
            10,
            1000,
            100,
            hWnd,
            (HMENU)NULL, // TODO can be used to set window ID
            hInstance,
            0);

        SendMessage(hTreeView, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
        SendMessage(hTreeView, TBM_SETPAGESIZE, 0, 4);
        SendMessage(hTreeView, TBM_SETSEL, FALSE, MAKELONG(20, 40));
        SendMessage(hTreeView, TBM_SETPOS, TRUE, 50);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_VSCROLL:
        break;
    case WM_HSCROLL:
        break;
    case WM_SIZE:
        break;
    case WM_COMMAND:
        break;
    case WM_NOTIFY:
        break;
    case WM_TIMER:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void WindowClassMain_Register(HINSTANCE hInstance)
{
    WNDCLASSEX wndClass = { 0 };

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WindowProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("WindowClassMain");

    RegisterClassEx(&wndClass);
}
