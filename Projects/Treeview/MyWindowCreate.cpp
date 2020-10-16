#include "api.h"

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
