#include <Windows.h>
#include <stdio.h>
#include <CommCtrl.h>

struct tab_window {
    LPCTSTR title;
    LPCTSTR class_name;
    HWND hwnd;
} tabWindow[] = {
    {TEXT("DrawLines"), TEXT("WindowClassDrawLines")},
    {TEXT("DrawRectangles"), TEXT("WindowClassDrawRectangles")}
};

static void TabAdd(HWND hWnd, int index, LPCTSTR title)
{
    TCITEM ti = { 0 };

    ti.mask = TCIF_TEXT;
    ti.pszText = (LPWSTR)title;
    ti.cchTextMax = wcslen(title);
    SendMessage(hWnd, TCM_INSERTITEM, index, (LPARAM)&ti);
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    INITCOMMONCONTROLSEX iccx;
    RECT rc;
    int iPage;

    static HWND hTabCtrl = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    switch (message)
    {
    case WM_CREATE:
        iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
        iccx.dwICC = ICC_TAB_CLASSES;
        if (!InitCommonControlsEx(&iccx))
            return FALSE;

        GetClientRect(hWnd, &rc);
        hTabCtrl = CreateWindowEx(
            0,
            WC_TABCONTROL,
            0,
            WS_CHILD | WS_VISIBLE,
            rc.left,
            rc.top,
            rc.right,
            rc.bottom,
            hWnd,
            NULL,
            hInstance,
            0);

        for (int i = 0; i < sizeof(tabWindow) / sizeof(tabWindow[0]); i++) {
            TabAdd(hTabCtrl, i, tabWindow[i].title);
        }

        GetClientRect(hTabCtrl, &rc);
        TabCtrl_AdjustRect(hTabCtrl, FALSE, &rc);
        
        for (int i = 0; i < sizeof(tabWindow) / sizeof(tabWindow[0]); i++) {
            tabWindow[i].hwnd = CreateWindowEx(
                0,
                tabWindow[i].class_name,
                0,
                WS_CHILD, // don't use VISIBLE style
                rc.left,
                rc.top,
                rc.right - rc.left, // 
                rc.bottom - rc.top, // Attention£º [[Windows API: TabControl]]
                hTabCtrl,
                NULL,
                hInstance,
                0);
        }

        ShowWindow(tabWindow[0].hwnd, SW_SHOW);
        break;
    case WM_SIZE:
        MoveWindow(hTabCtrl, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);

        GetClientRect(hTabCtrl, &rc);
        TabCtrl_AdjustRect(hTabCtrl, FALSE, &rc);
        for (int i = 0; i < sizeof(tabWindow) / sizeof(tabWindow[0]); i++) {
            MoveWindow(tabWindow[i].hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
        }
        break;
    case WM_NOTIFY:
        switch (((LPNMHDR)lParam)->code)
        {
        case TCN_SELCHANGING:
            iPage = TabCtrl_GetCurSel(((LPNMHDR)lParam)->hwndFrom);
            ShowWindow(tabWindow[iPage].hwnd, SW_HIDE);
            break;
        case TCN_SELCHANGE:
            iPage = TabCtrl_GetCurSel(((LPNMHDR)lParam)->hwndFrom);
            ShowWindow(tabWindow[iPage].hwnd, SW_SHOW);
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
