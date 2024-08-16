#ifndef API_H
#define API_H

#include <stdbool.h>
#define C_ERR 9
#define C_INFO 87

int rgb2xterm(int r, int g, int b);
typedef struct {
    int c256;
    int r;
    int g;
    int b;
} Color;

typedef struct {
    int width;
    int height;
} Size;

void mango_init(void);
bool mango_process(const char* path, int padding);
bool mango_is_valid_image_extension(const char *filename);

#endif //API_H