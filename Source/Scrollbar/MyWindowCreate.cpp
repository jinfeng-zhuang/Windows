#include "api.h"

HWND MyWindowCreate(int x, int y, int width, int height)
{
	return CreateWindowEx(0, MyWindowClassName, TEXT("MyWindow"), WS_OVERLAPPEDWINDOW,
		x, y, width, height,
		NULL, NULL, g_instance, NULL);
}
