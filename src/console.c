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

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return -1;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return -1;
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}