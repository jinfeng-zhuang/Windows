#include <Windows.h>
#include <stdio.h>
#include <Msg2String.h>
#include <hexdump.h>

#pragma warning(disable:4996)

TCHAR MyWindowClassName[] = TEXT("mainwindow");

HINSTANCE g_instance;

HWND hwndIP;
HWND hwndPort;
HWND hwndNetwork;
HWND hwndSend;
HWND hwndRecv;

#define SEND_BUFFER_SIZE    (1<<20)
#define RECV_BUFFER_SIZE    (1<<20)

TCHAR SendBuffer[SEND_BUFFER_SIZE];
char SendBuffer_ASCII[SEND_BUFFER_SIZE];
TCHAR RecvBuffer[RECV_BUFFER_SIZE];
char RecvBuffer_ASCII[RECV_BUFFER_SIZE];

#define MARGIN (20)

struct window_pos {
    int width_auto;
    int height_auto;
    int width_min;
    int height_min;

    int left;
    int top;
    int width;
    int height;
};

#define HEX_MODE

struct window_pos windows[] = {
    {0, 0, 200, 20},
    {1, 1, 400, 200},
    {1, 1, 400, 200},
    {0, 0, 100, 20},
    {0, 0, 100, 20},
};

int Adjust_Window_Position(HWND hwnd)
{
    int width;
    int height;
    RECT rect;

    GetClientRect(hwnd, &rect);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    windows[0].left = MARGIN;
    windows[0].top = MARGIN;
    windows[0].width = windows[0].width_min;
    windows[0].height = windows[0].height_min;
    
    windows[1].left = windows[0].left + windows[0].width_min + MARGIN;
    windows[1].top = MARGIN;
    windows[1].width = width - windows[1].left - MARGIN * 2;
    if (windows[1].width < windows[1].width_min) {
        windows[1].width = windows[1].width_min;
    }
    windows[1].height = height / 2 - MARGIN * 1.5;
    if (windows[1].height < windows[1].height_min) {
        windows[1].height = windows[1].height_min;
    }

    windows[2].left = windows[1].left;
    windows[2].top = windows[1].top + windows[1].height + MARGIN;
    windows[2].width = windows[1].width;
    windows[2].height = windows[1].height;

    windows[3].left = MARGIN;
    windows[3].top = windows[0].top + windows[0].height + MARGIN;
    windows[3].width = windows[3].width_min;
    windows[3].height = windows[3].height_min;

    windows[4].left = MARGIN;
    windows[4].top = windows[3].top + windows[3].height + MARGIN;
    windows[4].width = windows[4].width_min;
    windows[4].height = windows[4].height_min;

    MoveWindow(hwndIP, windows[0].left, windows[0].top, windows[0].width, windows[0].height, 1);
    MoveWindow(hwndPort, windows[3].left, windows[3].top, windows[3].width, windows[3].height, 1);
    MoveWindow(hwndNetwork, windows[4].left, windows[4].top, windows[4].width, windows[4].height, 1);
    MoveWindow(hwndRecv, windows[1].left, windows[1].top, windows[1].width, windows[1].height, 1);
    MoveWindow(hwndSend, windows[2].left, windows[2].top, windows[2].width, windows[2].height, 1);

    return 0;
}

int AppendRecvWindow(const char* str)
{
    MultiByteToWideChar(CP_ACP, 0, str, strlen(str), RecvBuffer, strlen(str));
    SetWindowText(hwndRecv, RecvBuffer);

    hexdump((unsigned char*)RecvBuffer, strlen(str) * sizeof(TCHAR));

    return 0;
}

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    unsigned int count;

    if ((uMsg == WM_CTLCOLOREDIT) ||
        (uMsg == WM_KEYDOWN) ||
        (uMsg == WM_COMMAND))
        printf("[%d] Window Message: %s (0x%04X): wParam %llx lParam %llx\n", GetTickCount(), Msg2String(uMsg), uMsg, wParam, lParam);
    //else
        //printf("Window Message: %s (0x%04X): wParam %llx lParam %llx\n", Msg2String(uMsg), uMsg, wParam, lParam);

    switch (uMsg)
    {
    case WM_CREATE:

        hwndIP = CreateWindowEx(
            0, // dwExStyle
            TEXT("Edit"),
            0,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
            10, 10, 200, 20,
            hWnd, // hWndParent
            NULL, // hMenu
            g_instance,
            NULL);

        hwndPort = CreateWindowEx(
            0, // dwExStyle
            TEXT("Edit"),
            0,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
            10, 10, 200, 20,
            hWnd, // hWndParent
            NULL, // hMenu
            g_instance,
            NULL);

        hwndNetwork = CreateWindowEx(
            0, // dwExStyle
            TEXT("Button"),
            TEXT("Network"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER,
            10, 10, 200, 20,
            hWnd, // hWndParent
            NULL, // hMenu
            g_instance,
            NULL);

        hwndRecv = CreateWindowEx(
            0, // dwExStyle
            TEXT("Edit"),
            0,
            WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
            220, 10, 500, 200,
            hWnd, // hWndParent
            NULL, // hMenu
            g_instance,
            NULL);

        hwndSend = CreateWindowEx(
            0, // dwExStyle
            TEXT("Edit"),
            0,
            WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_UPPERCASE | WS_VSCROLL | ES_AUTOVSCROLL,
            220, 250, 500, 200,
            hWnd, // hWndParent
            NULL, // hMenu
            g_instance,
            NULL);

        Adjust_Window_Position(hWnd);

        AppendRecvWindow("Hello\r\n World");

        printf("hWnd %p, hwndIP %p, hwndRecv %p, hwndSend %p\n", hWnd, hwndIP, hwndRecv, hwndSend);

        break;
    case WM_SIZE:
        Adjust_Window_Position(hWnd);
        break;
    case WM_KEYDOWN:
        break;
    case WM_COMMAND:
        if ((HWND)lParam == hwndSend) {
            if (HIWORD(wParam) == EN_CHANGE) {
                GetWindowText(hwndSend, SendBuffer, SEND_BUFFER_SIZE);
                count = wcslen(SendBuffer);
                WideCharToMultiByte(CP_ACP, 0, SendBuffer, -1, SendBuffer_ASCII, count, '\0', NULL);
                hexdump((unsigned char *)SendBuffer_ASCII, count);
                if ((SendBuffer_ASCII[count - 1] == '\n') && (GetAsyncKeyState(VK_CONTROL) < 0)) {
                    printf("Send to Network\n");
                }
            }
        }
        break;
    case WM_CTLCOLOREDIT:
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

int MyWindowRegister(void)
{
    WNDCLASSEX wce = { 0 };

    wce.cbSize = sizeof(wce);
    wce.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wce.hCursor = LoadCursor(NULL, IDC_ARROW);
    wce.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wce.hInstance = g_instance;
    wce.lpfnWndProc = MyWindowProc;
    wce.lpszClassName = MyWindowClassName;
    wce.style = CS_HREDRAW | CS_VREDRAW;
    if (!RegisterClassEx(&wce)) {
        return 1;
    }

    return 0;
}

HWND MyWindowCreate(int x, int y, int width, int height)
{
    return CreateWindowEx(
        0, // dwExStyle
        MyWindowClassName,
        TEXT("MyWindow"),
        WS_OVERLAPPEDWINDOW,
        x, y, width, height,
        NULL, // hWndParent
        NULL, // hMenu
        g_instance,
        NULL);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG msg;
    HWND hwnd;

    g_instance = hInstance;

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    MyWindowRegister();

    hwnd = MyWindowCreate(0, 0, 800, 600);
    if (hwnd == NULL) {
        printf("window_create failed");
        return false;
    }

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
