#include <Windows.h>
#include "common.h"

struct window_desc windows_desc_array[] = {
	{0, 0, 60, 60, BS_AUTORADIOBUTTON, TEXT("None")},
	{0, 60 + 20, 60, 60, BS_CHECKBOX, TEXT("None")},
	{0, 80 + 60 + 20, 60, 60, BS_PUSHBUTTON, TEXT("None")},
};

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HINSTANCE hInstance;
	int i;

	//printf("Window Message: 0x%04X\n", uMsg);

	hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

	switch (uMsg)
	{
	case WM_CREATE:
		for (i = 0; i < sizeof(windows_desc_array) / sizeof(windows_desc_array[0]); i++) {
			CreateWindowEx(
				0, // dwExStyle
				TEXT("Button"),
				windows_desc_array[i].value, // Title
				WS_CHILD | WS_VISIBLE | windows_desc_array[i].style,
				windows_desc_array[i].x,
				windows_desc_array[i].y,
				windows_desc_array[i].width,
				windows_desc_array[i].height,
				hWnd, // hWndParent
				NULL, // hMenu
				hInstance,
				NULL);
		}
		break;
	case WM_SIZE:
		break;
	case WM_KEYDOWN:
		break;
	case WM_COMMAND:
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

int MyButtonRegister(HINSTANCE hInstance)
{
	WNDCLASSEX wce = { 0 };

	wce.cbSize = sizeof(wce);
	wce.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wce.hInstance = hInstance;
	wce.lpfnWndProc = WindowProc;
	wce.lpszClassName = TEXT("MyButton");
	wce.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClassEx(&wce)) {
		return 1;
	}

	return 0;
}
