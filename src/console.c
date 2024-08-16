// console.c
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "console.h"

HANDLE console;
COORD initialPosition;

void initCursorPosition() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        initialPosition = csbi.dwCursorPosition;
    }
}

void resetCursorPosition() {
    SetConsoleCursorPosition(console, initialPosition);
}

void enableVirtualTerminalProcessing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void c256f(int color, const char *format, ...) {
    printf("\x1b[38;5;%dm", color);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\x1b[0m");
}

void c256gr(int range, int colors[], int size, const char *format, ...) {
    char buffer[1024];  // Adjust buffer size as needed
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    int len = strlen(buffer);
    int color_index = 0;
    int char_count = 0;
    bool reverse = false;

    for (int i = 0; i < len; i++) {
        if (char_count % range == 0) {
            printf("\x1b[38;5;%dm", colors[color_index]);

            if (!reverse) {
                color_index++;
                if (color_index >= size - 1) {
                    reverse = true;
                }
            } else {
                color_index--;
                if (color_index <= 0) {
                    reverse = false;
                }
            }
        }
        putchar(buffer[i]);
        char_count++;
    }
    printf("\x1b[0m");  // Reset color at the end
}

void c_clear() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    fill.Char.UnicodeChar = L' ';
    fill.Attributes = csbi.wAttributes;
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

Size getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    Size size = {-1, -1};

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
        return size;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return size;
    }
    size.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return size;
}