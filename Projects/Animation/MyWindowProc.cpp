#include "api.h"

HWND CreateAnimationCtrl(HWND hwndDlg)
{
	HWND hwndAnim = NULL;

	// Create the animation control.
	// IDC_ANIMATE - identifier of the animation control. 
	// hwndDlg - handle to the dialog box.
	RECT rc;
	hwndAnim = Animate_Create(hwndDlg, 0,
		WS_BORDER | WS_CHILD, g_instance);

	// Get the screen coordinates of the specified control button.
	// nIDCtl - identifier of the control below which the animation control is to be positioned.
	GetWindowRect(hwndDlg, &rc);

	// Convert the coordinates of the lower-left corner to 
	// client coordinates.
	POINT pt;
	pt.x = rc.left;
	pt.y = rc.bottom;
	ScreenToClient(hwndDlg, &pt);

	// Position the animation control below the Stop button.
	// CX_FRAME, CY_FRAME - width and height of the frames in the AVI clip.      
	SetWindowPos(hwndAnim, 0, pt.x, pt.y + 20,
		300, 300,
		SWP_NOZORDER | SWP_DRAWFRAME);

	// Open the AVI clip, and show the animation control.
	Animate_Open(hwndAnim, "SEARCH.AVI");
	ShowWindow(hwndAnim, SW_SHOW);

	return hwndAnim;
}

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	//printf("Window Message: 0x%04X\n", uMsg);

	switch (uMsg)
	{
	case WM_CREATE:
		CreateAnimationCtrl(hWnd);
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
