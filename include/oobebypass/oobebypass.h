#ifndef OOBEBYPASS_HEADER_H
#define OOBEBYPASS_HEADER_H

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#define USE_FONT "Segoe UI"

extern HFONT hFont;

HFONT InitFont(int pointSize);

void OnPaint(HWND hwnd, PAINTSTRUCT ps, HDC hdc);

#endif