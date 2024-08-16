#define STB_IMAGE_IMPLEMENTATION
#include "api.h"
#include "console.h"
#include "stb/stb_image.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WIDTH 256
#define ALPHA_THRESHOLD 128

int mango[4] = {203, 202, 208, 214};

static void outputBuffer(char* buffer, int length) {
    fwrite(buffer, 1, length, stdout);
}

void mango_init(void) {
    enableVirtualTerminalProcessing();
}

bool mango_is_valid_image_extension(const char *filename) {
    const char *extension = strrchr(filename, '.');
    if (extension == NULL) {
        return false;
    }

    char ext_lower[5];
    size_t i;
    for (i = 0; i < 4 && extension[i+1] != '\0'; i++) {
        ext_lower[i] = (char)tolower((unsigned char)extension[i+1]);
    }
    ext_lower[i] = '\0';

    return (strcmp(ext_lower, "png") == 0 ||
            strcmp(ext_lower, "jpg") == 0 ||
            strcmp(ext_lower, "jpeg") == 0 ||
            strcmp(ext_lower, "bmp") == 0 ||
            strcmp(ext_lower, "jfif") == 0 ||
            strcmp(ext_lower, "gif") == 0
            );
}

bool mango_process(const char* path, int padding) {
    if (!mango_is_valid_image_extension(path)) {
        c256f(C_ERR, "Error: Invalid file format. Supported formats are PNG, JPEG, BMP, JPG, JFIF, and GIF.\n");
        return false;
    }

    int width, height, channels;
    unsigned char *img = stbi_load(path, &width, &height, &channels, 4);

    if(img == NULL) {
        c256f(C_ERR, "Error in loading the image\n");
        return false;
    }

    c_clear();
    char buffer[MAX_WIDTH * 20];
    int bufferIndex;
    int lastColor = -1;

    for(int y = 0; y < height; y += padding) {
        bufferIndex = 0;
        for(int x = 0; x < width; x += padding) {
            unsigned char* p = img + (y * width + x) * 4;
            if(p[3] > ALPHA_THRESHOLD) {
                int a = rgb2xterm(p[0], p[1], p[2]);
                if (a != lastColor) {
                    bufferIndex += sprintf(buffer + bufferIndex, "\x1b[38;5;%dm", a);
                    lastColor = a;
                }
                buffer[bufferIndex++] = '@';
            } else {
                buffer[bufferIndex++] = ' ';
            }
        }
        buffer[bufferIndex++] = '\n';
        outputBuffer(buffer, bufferIndex);
    }

    printf("\x1b[0m\n");

    c256f(mango[0], "Info : \n");
    c256f(mango[3], "padding : %d\n", padding);
    c256f(mango[3], "size : %dx%d\n", (width/padding), (height/padding));
    c256f(mango[3],"origin : %s : (%dx%d)\n", path, width, height);

    stbi_image_free(img);
    return true;
}