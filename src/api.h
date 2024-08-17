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

typedef struct {
    int w;
    int h;
    int p;
    int max_w;  // Added max_width as part of the Mango struct
} Mango;

void mango_init(void);
bool mango_process(const char* path, Mango* mango);
bool mango_is_valid_image_extension(const char *filename);

#endif //API_H