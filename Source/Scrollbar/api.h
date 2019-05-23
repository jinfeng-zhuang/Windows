#ifndef API_H
#define API_H

//=============================================================================
// Headers
//=============================================================================

#include <Windows.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//=============================================================================
// Global Variables
//=============================================================================

extern HINSTANCE g_instance;

extern TCHAR MyWindowClassName[];

//=============================================================================
// API
//=============================================================================

extern int MyWindowRegister(void);
extern HWND MyWindowCreate(int x, int y, int width, int height);
extern LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif