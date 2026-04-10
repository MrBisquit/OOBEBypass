#include <oobebypass/oobebypass.h>

int page = 0;

HWND HWND_CANCEL_BTN = NULL;
HWND HWND_BACK_BTN = NULL;
HWND HWND_NEXT_BTN = NULL;

HWND HWND_BL_PROGRESS = NULL;

void OnPaint(HWND hwnd, PAINTSTRUCT ps, HDC hdc) {
    HFONT oldFont = SelectObject(hdc, hFont);

    switch(page) {
        case 0:

            break;
    }

    SelectObject(hdc, oldFont);
}

void OnCreate(HWND hwnd) {
    HWND_NEXT_BTN = CreateWindow(
        "BUTTON",
        "Next",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        800 - 75 - (50), 600 - 75, 100, 30,
        hwnd,
        (HMENU)WIN_NEXT_BTN,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    HWND_BACK_BTN = CreateWindow(
        "BUTTON",
        "Back",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_DISABLED,
        800 - 75 - (50 + 125), 600 - 75, 100, 30,
        hwnd,
        (HMENU)WIN_BACK_BTN,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    HWND_CANCEL_BTN = CreateWindow(
        "BUTTON",
        "Cancel",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        800 - 75 - (50 + 125 + 125), 600 - 75, 100, 30,
        hwnd,
        (HMENU)WIN_CANCEL_BTN,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_PROGRESS_CLASS };
    InitCommonControlsEx(&icc);

    HWND_BL_PROGRESS = CreateWindowExW(
        0,
        PROGRESS_CLASSW,
        NULL,
        WS_CHILD | WS_VISIBLE,
        // x y w h
        25, 600 - 75, 375, 30,
        hwnd,
        (HMENU)WIN_BL_PROGRESS,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    SendMessageW(HWND_BL_PROGRESS, PBM_SETPOS, 5, 0);
}