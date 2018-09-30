#include <stdio.h>
#include <stdint.h>


typedef struct bitmapfileheader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} fileheader;

typedef struct bitmapinfoheader {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} infoheader;

typedef struct rgb {
    int blue;
    int green;
    int red;
} rgb;

typedef struct bmp {
    fileheader header;
    infoheader info;
    rgb* color;
    rgb* to_swap;
} picture;


int load_bmp(char*, picture*);
int save_bmp(char*, picture*);
int crop(picture*, int, int, int, int);
int rotate(picture*);
int insert_message(picture*, char*, char*);
int extract_message(picture*, char*, char*);
