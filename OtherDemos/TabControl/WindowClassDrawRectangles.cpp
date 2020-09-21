#include <Windows.h>
#include <stdio.h>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance;
    RECT rc;
    HDC hdc;
    PAINTSTRUCT ps;

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_SIZE:
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rc);
        Rectangle(hdc, rc.left+2, rc.top+2, rc.right-2, rc.bottom-2);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void WindowClassDrawRectangles_Register(HINSTANCE hInstance)
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
    wndClass.lpszClassName = TEXT("WindowClassDrawRectangles");

    RegisterClassEx(&wndClass);
}