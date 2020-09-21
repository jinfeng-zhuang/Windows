#include <Windows.h>
#include <stdio.h>
#include <CommCtrl.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    TVINSERTSTRUCT tvs = { 0 };
    HTREEITEM root;

    static HWND hTreeView = 0; // TODO

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    switch (message)
    {
    case WM_CREATE:
        // TODO here no 'InitCommonControlsEx', why it can work
        GetClientRect(hWnd, &rc);
        hTreeView = CreateWindowEx(
            0,
            WC_TREEVIEW,
            0,
            WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT, // without TVS_LINESATROOT, child node hide
            rc.left,
            rc.top,
            rc.right,
            rc.bottom,
            hWnd,
            NULL,
            hInstance,
            0);

        tvs.item.mask = TVIF_TEXT;
        tvs.hInsertAfter = TVI_LAST;

        tvs.item.pszText = (LPWSTR)TEXT("Root");
        tvs.hParent = NULL;
        root = (HTREEITEM)SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvs);

        tvs.item.pszText = (LPWSTR)TEXT("Node1");
        tvs.hParent = NULL;
        SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvs);

        tvs.item.pszText = (LPWSTR)TEXT("Node2");
        tvs.hParent = NULL;
        SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)& tvs);

        tvs.item.pszText = (LPWSTR)TEXT("Node12");
        tvs.hParent = root;
        SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)& tvs);

        break;
    case WM_SIZE:
        MoveWindow(hTreeView, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
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
