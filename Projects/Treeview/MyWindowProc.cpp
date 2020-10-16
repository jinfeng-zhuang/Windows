#include "api.h"

TV_ITEMW tvi;

HTREEITEM AddItemToTree(
	HWND hwndTV,
	LPWSTR lpszItem,
	HTREEITEM hParent
)
{
	TVITEM tParent;
	TVINSERTSTRUCT tvins;
	HTREEITEM hme;

	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM;
	tvi.pszText = lpszItem;

	tvins.item = tvi;
	tvins.hInsertAfter = TVI_ROOT;
	if (hParent == NULL)
	{
		tvins.hParent = TVI_ROOT;
	}
	else
	{
		tvins.hParent = hParent;
	}

	hme = TreeView_InsertItem(hwndTV, &tvins);
	return hme;
}

bool InitTreeViewItems(HWND hwndTV)
{
	HTREEITEM hRoot = AddItemToTree(hwndTV, TEXT("input"), NULL);
	HTREEITEM hp = AddItemToTree(hwndTV, TEXT("document1"), hRoot);
	hp = AddItemToTree(hwndTV, TEXT("document2"), hRoot);
	return true;
}

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	RECT rcClient;
	HWND hwndTree;

	//printf("Window Message: 0x%04X\n", uMsg);

	switch (uMsg)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &rcClient);
		hwndTree =
			CreateWindowEx(
			WS_EX_CLIENTEDGE,
			WC_TREEVIEW,
			0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES,
			0, 0, rcClient.right, rcClient.bottom,
			hWnd, NULL, g_instance, NULL);
		InitTreeViewItems(hwndTree);
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
