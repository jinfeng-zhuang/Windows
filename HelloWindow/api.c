#include "app.h"

int window_class_create(HINSTANCE instance, LPCWSTR name, WNDPROC proc)
{
	WNDCLASSEX wce = { 0 };

	wce.cbSize = sizeof(wce);
	wce.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wce.hInstance = instance;
	wce.lpfnWndProc = proc;
	wce.lpszClassName = name;
	wce.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClassEx(&wce)) {
		return 1;
	}

	return 0;
}

HWND window_create(HINSTANCE instance, LPCWSTR name, int width, int height)
{
	HWND hwnd;

	hwnd = CreateWindowEx(0, name, TEXT(""), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
		NULL, NULL, instance, NULL);

	return hwnd;
}
