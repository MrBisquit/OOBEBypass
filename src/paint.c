#include <oobebypass/oobebypass.h>

int page = 0;

HWND HWND_CANCEL_BTN = NULL;
HWND HWND_BACK_BTN = NULL;
HWND HWND_NEXT_BTN = NULL;

HWND HWND_BL_PROGRESS = NULL;

void OnPaint(HWND hwnd, PAINTSTRUCT ps, HDC hdc) {
    HFONT oldFont = SelectObject(hdc, hFont);

    switch(page) {
        case 1:
            HFONT oldFont = SelectObject(hdc, hFont);
            SelectObject(hdc, InitFont(17));

            SetTextColor(hdc, RGB(128, 128, 255));
            SetBkMode(hdc, TRANSPARENT);

            RECT rect;
            rect.left = 15;
            rect.top = 15;
            rect.right = 300;
            rect.bottom = 50;

            DrawText(
                hdc,
                (LPCSTR)_T("Please wait...\0"),
                -1,
                &rect,
                DT_SINGLELINE | DT_TOP | DT_LEFT
            );

            SelectObject(hdc, hFont);

            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, TRANSPARENT);

            rect.top = 60;
            rect.left = 15;
            rect.bottom = 570;
            rect.right = 775;

            DrawText(
                hdc,
                (LPCSTR)_T("Bypassing the first stage of the OOBE, your computer will restart shortly.\n\n"
                    "At this stage, the program will enable the Administrator account, and disable the "
                    "Default account, then reboot.\0"),
                -1,
                &rect,
                DT_WORDBREAK | DT_TOP | DT_LEFT
            );

            EnableWindow(HWND_NEXT_BTN, 0);
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

    //SendMessage(HWND_NEXT_BTN, BCM_SETSHIELD, 1, 1);

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

    SendMessageW(HWND_BL_PROGRESS, PBM_SETPOS, 0, 0);

    if(page > 0) {
        EnableWindow(HWND_CANCEL_BTN, 0);
        UpdatePage(hwnd, page);
    }
}

void HandleBack(HWND hwnd) {

}

void HandleNext(HWND hwnd) {
    if(page == 0) {
        EnableWindow(HWND_CANCEL_BTN, 0);

        UpdatePage(hwnd, 1);
    }

    RECT clearArea = { 15, 15, 775, 775 };

    InvalidateRect(hwnd, &clearArea, 1);
    UpdateWindow(hwnd);
}

void UpdatePage(HWND hwnd, int _page) {
    int total_pages = 5;

    page = _page;

    float chunks = 100 / total_pages;
    float current = chunks * page;

    SendMessageW(HWND_BL_PROGRESS, PBM_SETPOS, current, 0);

    if(SaveState(&page) == 0) {
        MessageBox(
            hwnd,
            "Failed to save configuration file.",
            "OOBEBypass",
            MB_OK | MB_ICONERROR
        );
    }
}