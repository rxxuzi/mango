// console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <windows.h>
#include "api.h"

void enableVirtualTerminalProcessing();

extern HANDLE console;
extern COORD initialPosition;

void initCursorPosition(void);
void resetCursorPosition(void);
void c256(int color, const char *format);
void c256f(int color, const char *format, ...);
void c256gr(int range, int colors[], int size, const char *format, ...);
void c_clear();
Size getConsoleSize();
#ifdef __cplusplus
}
#endif
#endif // CONSOLE_H
