#include <Windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <CommCtrl.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;

    static HWND hComboBox = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    switch (message)
    {
    case WM_CREATE:
        // TODO here no 'InitCommonControlsEx', why it can work
        GetClientRect(hWnd, &rc);
        hComboBox = CreateWindowEx(
            0,
            TEXT("COMBOBOX"),
            0,
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // [[Windows API: ComboBox]]
            20,
            20,
            100,
            0, // ignored
            hWnd,
            (HMENU)NULL,
            hInstance,
            0);
        printf("Create ComboBox %p\n", hComboBox);
        ComboBox_AddString(hComboBox, TEXT("Test1"));
        ComboBox_AddString(hComboBox, TEXT("Test2"));
        break;
    case WM_SIZE:
        //MoveWindow(hComboBox, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
        break;
    case WM_NOTIFY:
        break;
    case WM_COMMAND:
        switch (HIWORD(wParam))
        {
        case CBN_SELCHANGE:
            printf("ComboBox Handle %x, ID %x, Sel %d\n", lParam, LOWORD(wParam), ComboBox_GetCurSel(hComboBox));
            break;
        }
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
