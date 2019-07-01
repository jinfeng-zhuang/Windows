#include <Windows.h>
#include "common.h"
#include "tinyxml2.h"

// stored as ANSI, but restored with Unicode, I don't know why
// there is a c code to copy data from harddisk to ddr, maybe the c code decode this
static const wchar_t html[] = L"<html><body><h1>Header1</h1><p>Hello ÄãºÃ HTML!</p></body></html>";

static wchar_t unicode_buffer[1024];
static int unicode_buffer_length = 1024;

static wchar_t utf8_buffer[1024];
static int utf8_buffer_length = 1024;

// css table
// global: consolas
// h1: 50
// h2: 40
// h3: 30
// p:  20
// b = i = ps

struct attr {
    const char name[32];
    int fontsize;
};

struct attr attr_map[] = {
    {"h1", 50},
    {"h2", 40},
    {"h3", 30},
    {"p", 20},
};

int draw_text(HDC hdc, RECT rect, COLORREF bgcolor, COLORREF fgcolor, int fontsize, SIZE *size)
{
    DRAWTEXTPARAMS drawtextparams;
    LOGFONT logicfont;
    HFONT hfont;
    int ret;
    int i;

    memset(&logicfont, 0, sizeof(logicfont));
    wsprintf(logicfont.lfFaceName, TEXT("Consolas"));
    logicfont.lfHeight = fontsize;
    hfont = CreateFontIndirect(&logicfont);
    SelectObject(hdc, hfont);
    GetTextExtentPoint(hdc, html, lstrlen(html), size);

    SetBkColor(hdc, bgcolor);
    SetTextColor(hdc, fgcolor);

    drawtextparams.cbSize = sizeof(DRAWTEXTPARAMS);
    drawtextparams.iTabLength = 2;
    drawtextparams.iLeftMargin = 1;
    drawtextparams.iRightMargin = 1;

    DrawTextEx(hdc, (wchar_t*)html, -1, &rect, DT_WORDBREAK | DT_EXPANDTABS, &drawtextparams);

    return 0;
}

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
    int ret;
    int i;
    SIZE size;

	//printf("Window Message: 0x%04X\n", uMsg);

	hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

	switch (uMsg)
	{
	case WM_CREATE:

        // detect the encode format

        // decode the ASCII/ANSI/UTF-8/... to UNICODE

        //ret = MultiByteToWideChar(CP_ACP, 0, (char *)html, lstrlen(html), unicode_buffer, unicode_buffer_length);
        //ret = WideCharToMultiByte(CP_UTF8, 0, unicode_buffer, ret, (char *)utf8_buffer, utf8_buffer_length, NULL, NULL);
        ret = WideCharToMultiByte(CP_UTF8, 0, html, lstrlen(html), (char *)utf8_buffer, utf8_buffer_length, NULL, NULL);
        (void)ret;
        doc.Parse((const char *)utf8_buffer);
        root = doc.RootElement();
        if (root) {
            body = root->FirstChildElement("body");
            if (body) {
                node = body->FirstChildElement();
                while (node) {
                    printf("%s: %s\n", node->Value(), node->GetText());
                    for (i = 0; i < sizeof(attr_map) / sizeof(attr_map[0]); i++) {
                        if (0 == strcmp(node->Value(), attr_map[i].name)) {
                            printf("size = %d\n", attr_map[i].fontsize);
                        }
                    }
                    node = node->NextSiblingElement();
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

        draw_text(hdc, clientrect, 0xFFFFFF, 0xFF0000, 50, &size);

        rect = clientrect;
        rect.top = 200;

        draw_text(hdc, rect, 0xFFFFFF, 0x0000FF, 20, &size);

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
