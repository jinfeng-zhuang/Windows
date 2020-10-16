#include "api.h"

HWND MyWindowCreate(int x, int y, int width, int height)
{
	return CreateWindowEx(
		0, // dwExStyle
		MyWindowClassName,
		TEXT("MyWindow"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		x, y, width, height,
		NULL, // hWndParent
		NULL, // hMenu
		g_instance,
		NULL);
}
