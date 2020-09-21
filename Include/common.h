#ifndef COMMON_H
#define COMMON_H

#include <Windows.h>
#include <stdio.h>
#include <process.h>

struct window_desc {
	int x;
	int y;
	int width;
	int height;
	DWORD style;
	wchar_t value[100];
};

extern void CustomWindowClassesInit(HINSTANCE hInstance);

extern void serial_port_list(void);

extern int DrawThread_Init(HWND hwnd);
extern int DrawCmd_Begin(BOOL empty);
extern void DrawCmd_End(void);
extern HDC DrawCmd_Get(void); // if empty, return old image
extern void DrawCmd_Rectangle(RECT rect, COLORREF color, BOOL fill);
extern void DrawCmd_Line(POINT a, POINT b);
extern void DrawCmd_Bitmap(HBITMAP bitmap, RECT rect);
extern void DrawCmd_Text(wchar_t* text, RECT rect);

#endif