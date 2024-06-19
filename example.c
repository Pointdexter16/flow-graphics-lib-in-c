#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include<string.h>
#include "flow.c"

#define Width 800
#define Heigth 600

static uint32_t pixels[Heigth * Width];

int main()
{
    const char *file_path = "output1.ppm";
    flow_fill(pixels, Width, Heigth, 0xFF00FF00);
    Errno err = flow_save_to_ppm(pixels, Width, Heigth, file_path);
    if (err)
    {
        printf("couldn't save the file %s: %s\n", file_path, strerror(err));
        return 1;
    }
    return 0;
}