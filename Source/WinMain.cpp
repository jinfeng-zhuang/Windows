#include "common.h"

extern void serial_port_list(void);
extern void clipboard_list(void);
extern const wchar_t* GetPredefinedClipboardFormatName(UINT format);

extern void HTMLShow(HWND hwnd, const WCHAR* text);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	HWND hwnd;
    FILE* fp;
    int filesize;
    char* content;
    wchar_t* unicode_content;

    //AllocConsole();
    //freopen("CONOUT$", "w", stdout);
    //freopen("log.txt", "w", stdout);

	// Custom Window Class Register
	CustomWindowClassesInit(hInstance);

	//clipboard_list();

	// Custom Window Create
	hwnd = CreateWindowEx(
		0, // dwExStyle
		TEXT("HTMLBoard"),
		TEXT("Demo"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL| WS_HSCROLL,
		300, 200, 1000, 400,
		NULL, // hWndParent
		NULL, // hMenu
		hInstance,
		NULL);

    fp = fopen("demo.html", "r");
    if (NULL != fp) {
        fseek(fp, 0, SEEK_END);
        filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        content = (char*)malloc(filesize + 1);
        memset(content, 0, filesize + 1);

        fread(content, 1, filesize, fp);

        unicode_content = (wchar_t*)malloc(filesize * 2);
        memset(unicode_content, 0, filesize * 2);

        MultiByteToWideChar(CP_UTF8, 0, (char *)content, strlen(content), unicode_content, filesize * 2);

        HTMLShow(hwnd, (const wchar_t *)unicode_content);
    }
    else {
        HTMLShow(hwnd, L"<html><body><p>File not found!</p></body></html>");
    }

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)(msg.wParam);
}
