#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include<string.h>

#ifndef FLOW_C_
#define FLOW_C_
#endif //FLOW_C_


#define return_defer(value) \
    do                      \
    {                       \
        result = (value);   \
        goto defer;         \
    } while (0)

typedef int Errno;

void flow_fill(uint32_t *pixels, size_t width, size_t heigth, uint32_t color)
{
    for (size_t i = 0; i < heigth * width; i++)
    {
        pixels[i] = color;
    }
}

Errno flow_save_to_ppm(uint32_t *pixels, size_t width, size_t heigth, const char *file_path)
{
    int result = 0;
    FILE *f = fopen(file_path, "wb");

    {
        if (f == NULL)
            return_defer(errno);
        fprintf(f, "P6\n%zu %zu 255\n", width, heigth);
        if (ferror(f))
            return_defer(errno);
        for (size_t i = 0; i < heigth * width; i++)
        {
            uint32_t pixel = pixels[i];
            uint8_t Bytes[3] = {
                (pixel >> (8 * 0)) & 0xFF,
                (pixel >> (8 * 1)) & 0xFF,
                (pixel >> (8 * 2)) & 0xFF,
            };
            fwrite(Bytes, sizeof(Bytes), 1, f);
        }
    }

defer:
    if (f)
        fclose(f);
    return result;
}
