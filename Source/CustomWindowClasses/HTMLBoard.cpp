#include <Windows.h>
#include "common.h"
#include "tinyxml2.h"

static const char html[] = "<html><body><h1>Header1</h1><p>Hello HTML!</p></body></html>";
static wchar_t whtml[100];

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HINSTANCE hInstance;
	TEXTMETRICW tm;
    RECT rect;
    RECT clientrect;
    DRAWTEXTPARAMS drawtextparams;
    COLORREF colorref;
    COLORREF bgcolor;
    LOGFONT logicfont;
    HFONT hfont;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *root;
    tinyxml2::XMLElement *body;
    tinyxml2::XMLElement*node;

	//printf("Window Message: 0x%04X\n", uMsg);

	hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

	switch (uMsg)
	{
	case WM_CREATE:

        doc.Parse(html);
        root = doc.RootElement();
        if (root) {
            body = root->FirstChildElement("body");
            if (body) {
                node = body->FirstChildElement();
                if (node) {
                    printf("%s: %s\n", node->Value(), node->GetText());
                    node = node->NextSiblingElement();
                    printf("%s: %s\n", node->Value(), node->GetText());
                }
            }
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

        GetClientRect(hWnd, &clientrect);

        memset(&logicfont, 0, sizeof(logicfont));
        wsprintf(logicfont.lfFaceName, TEXT("Consolas"));
        //logicfont.lfCharSet = GB2312_CHARSET;
        logicfont.lfHeight = 20;
        hfont = CreateFontIndirect(&logicfont);

        colorref = 0xFF0000;
        bgcolor = 0xFFFFFF;

        drawtextparams.cbSize = sizeof(DRAWTEXTPARAMS);
        drawtextparams.iTabLength = 2;
        drawtextparams.iLeftMargin = 1;
        drawtextparams.iRightMargin = 1;

        SelectObject(hdc, hfont);
        SetBkColor(hdc, bgcolor);
        SetTextColor(hdc, colorref);

        rect.top = 220;
        rect.left = 0;
        rect.right = clientrect.right;
        rect.bottom = 400;

        mbstowcs(whtml, html, strlen(html));

        DrawTextEx(hdc, whtml, -1, &rect, DT_WORDBREAK | DT_EXPANDTABS, &drawtextparams);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

int HTMLBoardRegister(HINSTANCE hInstance)
{
	WNDCLASSEX wce = { 0 };

	wce.cbSize = sizeof(wce);
	wce.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wce.hInstance = hInstance;
	wce.lpfnWndProc = WindowProc;
	wce.lpszClassName = TEXT("HTMLBoard");
	wce.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClassEx(&wce)) {
		return 1;
	}

	return 0;
}
