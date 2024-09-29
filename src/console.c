// console.c
#include "console.h"
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

static int _clamp(int value, int min, int max) {
    return (value < min) ? min : (value > max) ? max : value;
}

static void _hex_to_rgb(const char *hex, RGB *color) {
    if (hex[0] == '#') hex++;
    unsigned int hex_color = (unsigned int)strtol(hex, NULL, 16);
    color->r = (hex_color >> 16) & 0xFF;
    color->g = (hex_color >> 8) & 0xFF;
    color->b = hex_color & 0xFF;
}

void evtp(void) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#else
    // Linux doesn't need any special setup for ANSI escape codes
#endif
}

void c_clear(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void c_rgbf(RGB color, const char *format, ...) {
    printf("\x1b[38;2;%d;%d;%dm", color.r, color.g, color.b);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\x1b[0m");
}

void c_256f(int color, const char *format, ...) {
    printf("\x1b[38;5;%dm", color);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\x1b[0m");
}

void c_hexf(const char *hex, const char *format, ...) {
    RGB color;
    _hex_to_rgb(hex, &color);
    printf("\x1b[38;2;%d;%d;%dm", color.r, color.g, color.b);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\x1b[0m");
}

RGB newRGB(int r, int g, int b) {
    return (RGB){_clamp(r, 0, 255), _clamp(g, 0, 255), _clamp(b, 0, 255)};
}

int getConsoleWidth(void) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}