// console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RGB {
    int r;
    int g;
    int b;
} RGB;

// Function declarations
void evtp(void);
void c_clear(void);
int getConsoleWidth(void);
void c_rgbf(RGB color, const char *format, ...);
void c_256f(int color, const char *format, ...);
void c_hexf(const char *hex, const char *format, ...);
RGB newRGB(int r, int g, int b);
RGB hex_to_rgb(const char *hex);

#ifdef __cplusplus
}
#endif

#endif // CONSOLE_H
