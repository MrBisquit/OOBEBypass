#ifndef OOBEBYPASS_HEADER_H
#define OOBEBYPASS_HEADER_H

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include <shellapi.h>
#include <internal/internal.h>

#define USE_FONT "Segoe UI"

extern HFONT hFont;

BOOL IsProcessElevated();
BOOL RegisterForRestart();

void RestartAsAdmin();

HFONT InitFont(int pointSize);

void OnPaint(HWND hwnd, PAINTSTRUCT ps, HDC hdc);
void OnCreate(HWND hwnd);

void HandleBack(HWND hwnd);
void HandleNext(HWND hwnd);

void UpdatePage(HWND hwnd, int page);

enum {
    // Buttons on the bottom right
    WIN_CANCEL_BTN,
    WIN_BACK_BTN,
    WIN_NEXT_BTN,
    
    // Progress bar on the bottom left
    WIN_BL_PROGRESS,

    // Page 1
    WIN_P1_USERNAME,
    WIN_P1_PASSWORD
};

extern HWND HWND_CANCEL_BTN;
extern HWND HWND_BACK_BTN;
extern HWND HWND_NEXT_BTN;

extern HWND HWND_BL_PROGRESS;

// Inputs for page 1
extern HWND HWND_P1_USERNAME;
extern HWND HWND_P1_PASSWORD;

/*
    0 - Information page
    1 - Create local account page
    1 - 1st Progress page
        Essentially kills the OOBE
    2 - Gathering information page
    3 - 2nd Progress page
    4 - Finished page
*/
extern int page;

#endif