#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include<stdbool.h>
#include<string.h>
#include "flow.c"

#define Width 800
#define Height 600
#define BACKGROUND_COLOR 0xFF303030
#define WHITE 0xFFFFFFFF
#define FOREGROUND_COLOR 0xFF2020FF

#define ROWS 6
#define COLUMNS 8

static uint32_t pixels[Height * Width];

bool checker_example(){
    flow_fill(pixels,Width,Height,BACKGROUND_COLOR);
    int w=(Width/COLUMNS);
    int h=(Height/ROWS);
    uint32_t color;
    for(int x=0;x<COLUMNS;x++){
        for(int y=0;y<ROWS;y++){
            if((x+y)%2==0){
                color=BACKGROUND_COLOR;
            }
            else{
                color=0xFF2020FF;
            }
            flow_fill_rect(pixels,Width,Height,w*x,h*y,w,h,color);
        }
    }
    const char *file_path = "checker.ppm";
    Errno err = flow_save_to_ppm(pixels, Width, Height, file_path);
    if (err)
    {
        printf("couldn't save the file %s: %s\n", file_path, strerror(err));
        return false;
    }
    return true;
}

bool circle_example(){
    flow_fill(pixels,Width,Height,BACKGROUND_COLOR);
    flow_fill_circle(pixels,Width,Height,Width/2,Height/2,100,FOREGROUND_COLOR);
    const char *file_path = "circle.ppm";
    Errno err = flow_save_to_ppm(pixels, Width, Height, file_path);
    if (err)
    {
        printf("couldn't save the file %s: %s\n", file_path, strerror(err));
        return false;
    }
    return true;
}

int main()
{
    if(!circle_example()){
        return -1;
    }
    return 0;
}