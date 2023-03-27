#ifndef PIXEL_H
#define PIXEL_H
#include <stdint.h>

#pragma pack(push, 1)
typedef struct Pixel
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;
#pragma pack(pop)


#endif