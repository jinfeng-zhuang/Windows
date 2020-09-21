#include <Windows.h>
#include <stdio.h>
#include <CommCtrl.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    HDC hdc;
    PAINTSTRUCT ps;

    static HWND hEdit = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    //printf("%s: %x %x\n", __func__, wParam, lParam);

    switch (message)
    {
    case WM_CREATE:

        // timer priority is lowest
        // NULL means send WM_TIMER event to hWnd
        // hWnd is NULL means we need a callback
        SetTimer(hWnd, 0, 1, NULL); // ID 0 or not same means new timer, ID repeat means set timer to other value

        // TODO here no 'InitCommonControlsEx', why it can work
        GetClientRect(hWnd, &rc);
        hEdit = CreateWindowEx(
            0,
            TEXT("Edit"),
            0,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL,
            rc.left,
            rc.top,
            rc.right,
            rc.bottom,
            hWnd,
            (HMENU)NULL, // TODO can be used to set window ID
            hInstance,
            0);
        SendMessage(hEdit, EM_LIMITTEXT, 32 << 12, 0); // default is 32K TCHAR (not byte)
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
        MoveWindow(hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
        break;
    case WM_COMMAND:
        switch (HIWORD(wParam))
        {
        case EN_MAXTEXT:
            printf("reach the limit: %d\n", GetWindowTextLength(hEdit));
            break;
        }
        break;
    case WM_NOTIFY:
        break;
    case WM_TIMER:
        SendMessage(hEdit, EM_SETSEL, -2, -1);
        SendMessage(hEdit, EM_REPLACESEL, true, (LPARAM)TEXT("Hello World\n"));
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
