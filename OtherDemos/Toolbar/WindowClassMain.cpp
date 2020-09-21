#include <Windows.h>
#include <stdio.h>
#include <CommCtrl.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    HDC hdc;
    PAINTSTRUCT ps;
    INITCOMMONCONTROLSEX icex;

    static HWND hTreeView = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    //printf("%s: %x %x\n", __func__, wParam, lParam);

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 100, NULL);

        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
        InitCommonControlsEx(&icex);
        
        // TODO here no 'InitCommonControlsEx', why it can work
        GetClientRect(hWnd, &rc);
        hTreeView = CreateWindowEx(
            0,
            TOOLBARCLASSNAME,
            0,
            WS_CHILD | WS_VISIBLE | TBSTYLE_WRAPABLE,
            //rc.left, rc.top, rc.right, rc.bottom,
            0, 0, 0, 0,
            hWnd,
            (HMENU)NULL, // TODO can be used to set window ID
            hInstance,
            0);
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
