#include <Windows.h>
#include <stdio.h>
#include <CommCtrl.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    HDC hdc;
    PAINTSTRUCT ps;
    INITCOMMONCONTROLSEX iccx;

    static HWND hEdit = 0; // TODO
    static HWND hUpDown = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    //printf("%s: %x %x\n", __func__, wParam, lParam);

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 100, NULL);

        iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
        iccx.dwICC = ICC_UPDOWN_CLASS;
        InitCommonControlsEx(&iccx);

        // TODO here no 'InitCommonControlsEx', why it can work
        GetClientRect(hWnd, &rc);

        hEdit = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            TEXT("EDIT"),
            0,
            WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_LEFT,
            //rc.left, rc.top, rc.right, rc.bottom,
            20, 20, 100, 24,
            hWnd,
            (HMENU)NULL, // TODO can be used to set window ID
            hInstance,
            0);

        hUpDown = CreateWindowEx(
            0,
            UPDOWN_CLASS,
            0,
            WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_SETBUDDYINT,
            0, 0, 0, 0, // Note: take no effect on this control
            hWnd,
            (HMENU)NULL, // TODO can be used to set window ID
            hInstance,
            0);

        SendMessage(hUpDown, UDM_SETBUDDY, (WPARAM)hEdit, 0);

        SendMessage(hUpDown, UDM_SETRANGE, 0, MAKELPARAM(-5, 5));
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
