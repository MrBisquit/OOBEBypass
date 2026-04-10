#include <oobebypass/oobebypass.h>

int page = 0;

void OnPaint(HWND hwnd, PAINTSTRUCT ps, HDC hdc) {
    HFONT oldFont = SelectObject(hdc, hFont);

    switch(page) {
        case 0:

            break;
    }

    SelectObject(hdc, oldFont);
}