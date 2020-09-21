#include <Windows.h>
#include <stdio.h>
#include <process.h>
#include <assert.h>

#include <ft2build.h>
#include FT_FREETYPE_H

extern int BGRABoardRegister(HINSTANCE hInstance);
extern void BGRABoard_Set(unsigned char *buffer, int width, int height);

FT_Library library;
FT_Face face;
FT_UInt index;

int Gray2BGRA(unsigned char *bgra, unsigned char *gray, unsigned int size)
{
    int i;

    for (i = 0; i < size; i++) {
        bgra[i * 4 + 0] = gray[i];
        bgra[i * 4 + 1] = gray[i];
        bgra[i * 4 + 2] = gray[i];
        bgra[i * 4 + 3] = 0xFF;
    }

    return 0;
}

//https://blog.csdn.net/finewind/article/details/38009731s
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HWND hwnd;
    MSG msg;
    int ret;
    
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    FT_Init_FreeType(&library);

    ret = FT_New_Face(library, "C:/Windows/Fonts/simsun.ttc", 0, &face);
    assert(0 == ret);

    FT_Set_Char_Size(face, 16*64*20, 16*64*20, 96, 96);

    // if index == 0, use another face which is set by user
    index = FT_Get_Char_Index(face, TEXT('x'));

    FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);

    if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

#if 0
    ft2CopyBitmapToBuf(buffer, startX+face->glyph->bitmap_left,
		startY+face->size->metrics.ascender/64-face->glyph->bitmap_top,
		face->glyph->bitmap);
	startX += face->glyph->advance.x/64;
#endif

    BGRABoardRegister(hInstance);

    hwnd = CreateWindowEx(
        0, // dwExStyle
        TEXT("BGRABoard"),
        TEXT("BGRA"), // Title
        WS_MINIMIZE,
        0, 0, 800, 600,
        NULL, // hWndParent
        NULL, // hMenu
        hInstance,
        NULL);

    unsigned char* bgra = (unsigned char*)malloc(face->glyph->bitmap.width * face->glyph->bitmap.rows * 4);
    Gray2BGRA(bgra, face->glyph->bitmap.buffer, face->glyph->bitmap.width * face->glyph->bitmap.rows);
    BGRABoard_Set(bgra, face->glyph->bitmap.width, face->glyph->bitmap.rows);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)(msg.wParam);
}

