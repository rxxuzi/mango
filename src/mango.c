#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "api.h"
#include "console.h"
#include "stb/stb_image.h"
#include "stb/stb_image_resize2.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHA_THRESHOLD 128

static int colors[4] = {203, 202, 208, 214};

static void outputBuffer(char* buffer, int length) {
    fwrite(buffer, 1, length, stdout);
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

bool mango_process(const char* path, Mango* mango) {
    if (!mango_is_valid_image_extension(path)) {
        c_256f(C_ERR, "Error: Invalid file format. Supported formats are PNG, JPEG, BMP, JPG, JFIF, and GIF.\n");
        return false;
    }

    int width, height, channels;
    unsigned char *img = stbi_load(path, &width, &height, &channels, 4);

    if(img == NULL) {
        c_256f(C_ERR, "Error in loading the image\n");
        return false;
    }

    Mango origin = {width, height, mango->p, mango->max_w};
    *mango = origin;  // Update mango with the original dimensions

    if (mango->w > mango->max_w) {
        mango->h = (int)((float)mango->h * mango->max_w / mango->w);
        mango->w = mango->max_w;
    }

    // Resize image if necessary
    unsigned char *resized_img = img;
    if (mango->w != origin.w || mango->h != origin.h) {
        resized_img = (unsigned char*)malloc(mango->w * mango->h * 4);
        if (!stbir_resize_uint8_srgb(img, origin.w, origin.h, 0, resized_img, mango->w, mango->h, 0, 4)) {
            c_256f(C_ERR, "Error in resizing the image\n");
            stbi_image_free(img);
            return false;
        }
    }

    c_clear();
    char buffer[mango->max_w * 20];
    int bufferIndex;
    int lastColor = -1;

    for(int y = 0; y < mango->h; y += mango->p) {
        bufferIndex = 0;
        for(int x = 0; x < mango->w; x += mango->p) {
            unsigned char* p = resized_img + (y * mango->w + x) * 4;
            if(p[3] > ALPHA_THRESHOLD) {
                int a = rgb2xterm(p[0], p[1], p[2]);
                if (a != lastColor) {
                    bufferIndex += sprintf(buffer + bufferIndex, "\x1b[38;5;%dm", a);
                    lastColor = a;
                }
                buffer[bufferIndex++] = '#';
            } else {
                buffer[bufferIndex++] = ' ';
            }
        }
        buffer[bufferIndex++] = '\n';
        outputBuffer(buffer, bufferIndex);
    }

    printf("\x1b[0m\n");

    c_256f(colors[0], "Info : \n");
    c_256f(colors[3], "padding : %d\n", mango->p);
    c_256f(colors[3], "size : %dx%d\n", (mango->w / mango->p), (mango->h / mango->p));
    c_256f(colors[3], "origin : %s : (%dx%d)\n", path, origin.w, origin.h);

    if (resized_img != img) {
        free(resized_img);
    }
    stbi_image_free(img);
    return true;
}