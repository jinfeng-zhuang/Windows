#ifndef COMMON_H
#define COMMON_H

#include <Windows.h>
#include <stdio.h>

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

#endif