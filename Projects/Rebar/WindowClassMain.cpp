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
    REBARBANDINFO rbBand = { sizeof(REBARBANDINFO) };

    static HWND hRebar = 0; // TODO
    static HWND hComboBox = 0;

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    //printf("%s: %x %x\n", __func__, wParam, lParam);

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 100, NULL);

        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
        InitCommonControlsEx(&icex);

#if 1
        hComboBox = CreateWindowEx(
            0,
            TEXT("COMBOBOX"),
            0,
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // [[Windows API: ComboBox]]
            //20, 20, 100, 100,
            100, 100, 100, 0,
            hWnd,
            (HMENU)NULL,
            hInstance,
            0);
#endif

        // TODO here no 'InitCommonControlsEx', why it can work
        GetClientRect(hWnd, &rc);
        hRebar = CreateWindowEx(
            WS_EX_TOOLWINDOW, // TODO
            REBARCLASSNAME,
            0,
            WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | RBS_VARHEIGHT | CCS_NODIVIDER | RBS_BANDBORDERS, // TODO: WS_CLIPSIBLINGS 
            //rc.left, rc.top, rc.right, rc.bottom,
            0, 0, 0, 0, // TODO
            hWnd,
            (HMENU)NULL, // TODO can be used to set window ID
            hInstance,
            0);

        rbBand.fMask =
            RBBIM_STYLE       // fStyle is valid.
            | RBBIM_TEXT        // lpText is valid.
            | RBBIM_CHILD       // hwndChild is valid.
            | RBBIM_CHILDSIZE   // child size members are valid.
            | RBBIM_SIZE;       // cx is valid
        rbBand.fStyle = RBBS_CHILDEDGE | RBBS_GRIPPERALWAYS;

        // Get the height of the toolbar.
        //DWORD dwBtnSize = (DWORD)SendMessage(hwndToolbar, TB_GETBUTTONSIZE, 0, 0);

        // Set values unique to the band with the toolbar.
        rbBand.lpText = (LPWSTR)TEXT("");
        //rbBand.hwndChild = hwndToolbar;
        //rbBand.cyChild = LOWORD(dwBtnSize);
        //rbBand.cxMinChild = NUMBUTTONS * HIWORD(dwBtnSize);
        //rbBand.cyMinChild = LOWORD(dwBtnSize);
        // The default width is the width of the buttons.
        rbBand.cx = 0;

        // Add the band that has the toolbar.
        SendMessage(hRebar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)& rbBand);

        // Set values unique to the band with the combo box.
        RECT rc;
        GetWindowRect(hComboBox, &rc);
        rbBand.lpText = (LPWSTR)TEXT("Font");
        rbBand.hwndChild = hComboBox;
        rbBand.cxMinChild = 0;
        rbBand.cyMinChild = rc.bottom - rc.top;
        // The default width should be set to some value wider than the text. The combo 
        // box itself will expand to fill the band.
        rbBand.cx = 100;

        // Add the band that has the combo box.
        SendMessage(hRebar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)& rbBand);
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
