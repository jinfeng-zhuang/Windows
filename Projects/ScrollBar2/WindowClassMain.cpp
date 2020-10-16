#include <Windows.h>
#include <CommCtrl.h>
#include <stdio.h>
#include <assert.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    BITMAP bmpinfo;
    HDC hdc;
    PAINTSTRUCT ps;
    
    static HBITMAP bitmap = { 0 }; // TODO
    static int cxClient, cyClient, cxBitmap, cyBitmap;
    static HDC hdcBitmap;
    static int iHScrollBarPos = 0, iVScrollBarPos = 0; // TODO: scroll bar status

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    //printf("%s: %x %x\n", __func__, wParam, lParam);

    switch (message)
    {
    case WM_CREATE:
        bitmap = (HBITMAP)LoadImage(NULL, TEXT("example.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        assert(bitmap != NULL);

        hdc = GetDC(hWnd);
        hdcBitmap = CreateCompatibleDC(hdc);
        SelectObject(hdcBitmap, bitmap);
        ReleaseDC(hWnd, hdc);

        GetObject(bitmap, sizeof(BITMAP), &bmpinfo);
        cxBitmap = bmpinfo.bmWidth;
        cyBitmap = bmpinfo.bmHeight;

        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        printf("iVScrollBarPos %d\n", -iVScrollBarPos);

        BitBlt(hdc, -iHScrollBarPos, -iVScrollBarPos, cxBitmap, cyBitmap, hdcBitmap, 0, 0, SRCCOPY);

        EndPaint(hWnd, &ps);
        break;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        SetScrollRange(hWnd, SB_HORZ, 0, cxBitmap - cxClient, FALSE); // TODO: cxBitmap < cxClient ?
        SetScrollRange(hWnd, SB_VERT, 0, cyBitmap - cyClient, FALSE);

        iHScrollBarPos = min(cxBitmap - cxClient, max(0, iHScrollBarPos)); // limit range [min, max]
        iVScrollBarPos = min(cyBitmap - cyClient, max(0, iVScrollBarPos));

        if (iHScrollBarPos != GetScrollPos(hWnd, SB_HORZ)) {
            SetScrollPos(hWnd, SB_HORZ, iHScrollBarPos, TRUE);
            InvalidateRect(hWnd, NULL, FALSE);
        }

        if (iVScrollBarPos != GetScrollPos(hWnd, SB_VERT)) {
            SetScrollPos(hWnd, SB_VERT, iVScrollBarPos, SB_VERT);
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;
    case WM_NOTIFY:
        break;
    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_THUMBTRACK:
            iVScrollBarPos = HIWORD(wParam);
            break;
        }

        // limit the range
        iVScrollBarPos = min(cyBitmap - cyClient, max(0, iVScrollBarPos));

        // if iVScrollBarPos not same as current, update and invalidate client area
        if (iVScrollBarPos != GetScrollPos(hWnd, SB_VERT)) {
            SetScrollPos(hWnd, SB_VERT, iVScrollBarPos, TRUE);
            InvalidateRect(hWnd, NULL, FALSE); // to avoid blink, don't erase background, just cover with new frame
        }
        break;
    case WM_HSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_THUMBTRACK:
            iHScrollBarPos = HIWORD(wParam);
            break;
        }

        // limit the range
        iHScrollBarPos = min(cxBitmap - cxClient, max(0, iHScrollBarPos));

        // if iVScrollBarPos not same as current, update and invalidate client area
        if (iHScrollBarPos != GetScrollPos(hWnd, SB_HORZ)) {
            SetScrollPos(hWnd, SB_HORZ, iHScrollBarPos, TRUE);
            InvalidateRect(hWnd, NULL, FALSE); // to avoid blink, don't erase background, just cover with new frame
        }
        break;
    case WM_DESTROY:
        DeleteDC(hdcBitmap);

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
