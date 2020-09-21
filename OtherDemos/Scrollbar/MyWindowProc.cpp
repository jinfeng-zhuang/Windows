#include "api.h"

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	int client_width, client_height;

	SCROLLINFO si;

	//printf("Window Message: 0x%04X\n", uMsg);

	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_SIZE:
		client_width = LOWORD(lParam);
		client_height = HIWORD(lParam);

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 1000 - 1;	// 1000 lines - 1, as start from 0
		si.nPage = 500;	// each page contain 100 lines
		SetScrollInfo(hWnd, SB_VERT, &si, true);
		break;
	case WM_VSCROLL:
		si.fMask = SIF_RANGE | SIF_POS;
		GetScrollInfo(hWnd, SB_VERT, &si); 
		printf("Current Position %d, Scroll to %d, %x %x\n", si.nPos, HIWORD(wParam), wParam, lParam);

		if (SB_THUMBTRACK == LOWORD(wParam)) {
			si.fMask = SIF_POS;
			si.nPos = HIWORD(wParam);
			SetScrollInfo(hWnd, SB_VERT, &si, true);
		}
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
