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

/*
    0 - Information page
    1 - 1st Progress page
        Essentially kills the OOBE
    2 - Gathering information page
    3 - 2nd Progress page
*/
extern int page;

#endif