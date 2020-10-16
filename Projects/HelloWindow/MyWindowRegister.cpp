#include "api.h"

TCHAR MyWindowClassName[] = TEXT("mainwindow");

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