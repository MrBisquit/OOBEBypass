#include <oobebypass/oobebypass.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    LPCSTR title = _T("Welcome to OOBEBypass\0");
    LPCSTR descr = _T("This guide will take you through bypassing the OOBE, "
    "and creating a local account. This will bypass the OOBE entirely, press "
    "\"Next\" at the bottom right to start.\n\n"
    "It is important to note that after pressing next on this page, you cannot "
    "go back, and the option to cancel will be disabled. If you wish to cancel, "
    "please do so now.\0");

    switch(uMsg) {
        case WM_CREATE:
            hFont = InitFont(12);

            OnCreate(hwnd);

            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            HFONT oldFont = SelectObject(hdc, hFont);
            SelectObject(hdc, InitFont(17));

            SetTextColor(hdc, RGB(128, 128, 255));
            SetBkMode(hdc, TRANSPARENT);

            RECT rect;
            rect.left = 15;
            rect.top = 15;
            rect.right = 300;
            rect.bottom = 50;

            DrawText(hdc, title, -1, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT);

            SelectObject(hdc, hFont);

            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, TRANSPARENT);

            rect.top = 60;
            rect.left = 15;
            rect.bottom = 570;
            rect.right = 775;

            DrawText(hdc, descr, -1, &rect, DT_WORDBREAK | DT_TOP | DT_LEFT);

            //TextOut(hdc, 15, 15, title, _tcslen(title));
            //TextOut(hdc, 15, 40, descr, _tcslen(descr));

            SelectObject(hdc, oldFont);

            OnPaint(hwnd, ps, hdc);

            EndPaint(hwnd, &ps);
            break;
        case WM_COMMAND:
            if(LOWORD(wParam) == WIN_CANCEL_BTN) {
                // Set the progress to 0% just because why not
                SendMessageW(HWND_BL_PROGRESS, PBM_SETPOS, 0, 0);

                // Hide the window
                ShowWindow(hwnd, 0);

                // Say no changes were made
                MessageBox(
                    hwnd,
                    "No changes were made, you can continue with the built-in OOBE.\n\n"
                    "Made by WTDawson (MrBisquit on GitHub)\n"
                    "https://github.com/MrBisquit/OOBEBypass",
                    "OOBEBypass",
                    MB_OK | MB_ICONINFORMATION
                );

                // Die
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "WTDawson.OOBEBypass";

    INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_WIN95_CLASSES | ICC_BAR_CLASSES | ICC_PROGRESS_CLASS };
    InitCommonControlsEx(&icc);

    /*WNDCLASS wc;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);*/

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WindowProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = CLASS_NAME;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Failed to register class"),
            _T("OOBEBypass"),
            MB_OK);

        return 1;
    }

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Win11 OOBE Bypass by WTDawson (MrBisquit on GitHub)",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(hwnd == NULL) {
        MessageBox(NULL, _T("Failed to create Window"), _T("OOBEBypass"), MB_OK);
        return 0;
    }

    /*HMENU hMenu = GetSystemMenu(hwnd, FALSE);
    if(hMenu) {
        EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    }

    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);*/

    // Disable the window icon, buttons, resizing
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_SIZEBOX; // Remove size box (disables resizing)
    style &= ~WS_SYSMENU; // Remove window icon and buttons
    SetWindowLong(hwnd, GWL_STYLE, style);

    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}