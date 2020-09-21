#include <Windows.h>
#include <stdio.h>
#include <CommCtrl.h>

static void ListAdd(HWND hWnd)
{
    LV_COLUMN lvc;

    lvc.mask = LVCF_TEXT | LVCF_WIDTH;

    lvc.pszText = (LPWSTR)TEXT("学号");
    lvc.cx = 60;
    SendMessage(hWnd, LVM_INSERTCOLUMN, 0, (long)& lvc); // TODO index

    lvc.pszText = (LPWSTR)TEXT("姓名");
    lvc.cx = 60;
    SendMessage(hWnd, LVM_INSERTCOLUMN, 1, (long)& lvc);
}

static void ItemAdd(HWND hWnd)
{
    int i;
    wchar_t number[16] = { 0 };
    LVITEM vitem = { 0 };

    vitem.mask = LVIF_TEXT;

    for (i = 0; i < 100; i++) {
        vitem.iItem = i; // the row number

        wsprintf(number, L"%d", i + 1000);

        vitem.iSubItem = 0; // the column number
        vitem.pszText = (LPWSTR)number;
        SendMessage(hWnd, LVM_INSERTITEM, 1, (long)& vitem);

        vitem.iSubItem = 1;
        vitem.pszText = (LPWSTR)TEXT("王富贵");
        SendMessage(hWnd, LVM_SETITEM, 0, (long)& vitem);
    }
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    

    static HWND hListView = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    switch (message)
    {
    case WM_CREATE:
        // TODO here no 'InitCommonControlsEx', why it can work
        GetClientRect(hWnd, &rc);
        hListView = CreateWindowEx(
            0,
            WC_LISTVIEW,
            0,
            WS_CHILD | WS_VISIBLE | LVS_REPORT, // Attention
            rc.left,
            rc.top,
            rc.right,
            rc.bottom,
            hWnd,
            NULL,
            hInstance,
            0);

        ListAdd(hListView);
        ItemAdd(hListView);
        break;
    case WM_SIZE:
        MoveWindow(hListView, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
        break;
    case WM_NOTIFY:
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
