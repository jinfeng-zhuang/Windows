#ifndef API_H
#define API_H

#include <Windows.h>

int window_class_create(HINSTANCE instance, LPCWSTR name, WNDPROC func);
HWND window_create(HINSTANCE instance, LPCWSTR name, int width, int height);

#endif