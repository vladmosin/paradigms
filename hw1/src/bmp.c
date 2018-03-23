#include <string.h>
#include <stdio.h>
#include <bmp.h>
#include <stdlib.h>


int load_bmp(char* filename, picture* bmp) {
    FILE* f = fopen(filename, "rb");
    if (f == NULL)
        return 1;

    fileheader* bmfh = &bmp->header;
    fread(&bmfh->bfType, 2, 1, f);
    fread(&bmfh->bfSize, 4, 1, f);
    fread(&bmfh->bfReserved1, 2, 1, f);
    fread(&bmfh->bfReserved2, 2, 1, f);
    fread(&bmfh->bfOffBits, 4, 1, f);

    infoheader* bmih = &bmp->info;
    fread(&bmih->biSize, 4, 1, f);
    fread(&bmih->biWidth, 4, 1, f);
    fread(&bmih->biHeight, 4, 1, f);
    fread(&bmih->biPlanes, 2, 1, f);
    fread(&bmih->biBitCount, 2, 1, f);
    fread(&bmih->biCompression, 4, 1, f);
    fread(&bmih->biSizeImage, 4, 1, f);
    fread(&bmih->biXPelsPerMeter, 4, 1, f);   
    fread(&bmih->biYPelsPerMeter, 4, 1, f);
    fread(&bmih->biClrUsed, 4, 1, f);
    fread(&bmih->biClrImportant, 4, 1, f);

    bmp->color = (rgb*) calloc(bmih->biWidth * bmih->biHeight, sizeof(rgb));
    if (bmp->color == NULL)
        return 1;
    int bias = bmih->biWidth % 4;
    int zeroes = 0;
    for (int i = 0; i < bmih->biHeight; i++) {
        for (int j = 0; j < bmih->biWidth; j++) {
            fread(&bmp->color[i * bmih->biWidth + j].blue, 1, 1, f);
            fread(&bmp->color[i * bmih->biWidth + j].green, 1, 1, f);
            fread(&bmp->color[i * bmih->biWidth + j].red, 1, 1, f);
        }
        fread(&zeroes, bias, 1, f);
    }
    fclose(f);
    return 0;
}

int save_bmp(char* filename, picture* bmp) {
    FILE* f = fopen(filename, "wb");
    if (f == NULL)
        return 1;
    
    fileheader* bmfh = &bmp->header;
    int bias = bmp->info.biWidth % 4;
    bmfh->bfSize = 54 + (3 * bmp->info.biWidth + bias) * bmp->info.biHeight;
    fwrite(&bmfh->bfType, 2, 1, f);
    fwrite(&bmfh->bfSize, 4, 1, f);
    fwrite(&bmfh->bfReserved1, 2, 1, f);
    fwrite(&bmfh->bfReserved2, 2, 1, f);
    fwrite(&bmfh->bfOffBits, 4, 1, f);

    infoheader* bmih = &bmp->info;
    bmih->biSizeImage = bmfh->bfSize - 54;
    fwrite(&bmih->biSize, 4, 1, f);
    fwrite(&bmih->biWidth, 4, 1, f);
    fwrite(&bmih->biHeight, 4, 1, f);
    fwrite(&bmih->biPlanes, 2, 1, f);
    fwrite(&bmih->biBitCount, 2, 1, f);
    fwrite(&bmih->biCompression, 4, 1, f);
    fwrite(&bmih->biSizeImage, 4, 1, f);
    fwrite(&bmih->biXPelsPerMeter, 4, 1, f);   
    fwrite(&bmih->biYPelsPerMeter, 4, 1, f);
    fwrite(&bmih->biClrUsed, 4, 1, f);
    fwrite(&bmih->biClrImportant, 4, 1, f);

    int zeroes = 0;
    for (int i = 0; i < bmih->biHeight; i++) {
        for (int j = 0; j < bmih->biWidth; j++) {
            fwrite(&bmp->color[i * bmih->biWidth + j].blue, 1, 1, f);
            fwrite(&bmp->color[i * bmih->biWidth + j].green, 1, 1, f);
            fwrite(&bmp->color[i * bmih->biWidth + j].red, 1, 1, f);
        }
        fwrite(&zeroes, bias, 1, f);
    }
    fclose(f);
    return 0;
}

int crop(picture* bmp, int x, int y, int width, int height) {
    if (x + width > bmp->info.biWidth || y + height > bmp->info.biHeight)
        return 1;
    bmp->to_swap = (rgb*) malloc(sizeof(rgb) * height * width);
    if (bmp->to_swap == NULL)
        return 1;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            memcpy(&bmp->to_swap[i * width + j], &bmp->color[(bmp->info.biHeight - y - height + i) * bmp->info.biWidth + j + x], sizeof(rgb));
    free(bmp->color);
    bmp->color = bmp->to_swap;
    bmp->to_swap = NULL;
    bmp->info.biWidth = width;
    bmp->info.biHeight = height;
    return 0;
}

int rotate(picture* bmp) {
    bmp->to_swap = (rgb*) malloc(sizeof(rgb) * bmp->info.biWidth * bmp->info.biHeight);
    if (bmp->to_swap == NULL)
        return 1;
    for (int i = 0; i < bmp->info.biHeight; i++)
        for (int j = 0; j < bmp->info.biWidth; j++)
            memcpy(&bmp->to_swap[bmp->info.biHeight * (bmp->info.biWidth - j - 1) + i], &bmp->color[i * bmp->info.biWidth + j], sizeof(rgb));
    free(bmp->color);
    bmp->color = bmp->to_swap;
    bmp->to_swap = NULL;
    int height = bmp->info.biWidth;
    bmp->info.biWidth = bmp->info.biHeight;
    bmp->info.biHeight = height;
    return 0;
}

void change_color(int* color, int bit) {
    *color -= (*color) % 2 + bit;
}

void insert_letter(picture* bmp, FILE* f, int number) {
    int x = 0, y = 0;
    char color = ' ';
    for (int i = 0; i < 5; i++) {
        fscanf(f, "%d%d%c%c", &x, &y, &color, &color);
        if (color == 'B')
            change_color(&bmp->color[x + bmp->info.biWidth * (bmp->info.biHeight - y - 1)].blue, number % 2);
        if (color == 'R')
            change_color(&bmp->color[x + bmp->info.biWidth * (bmp->info.biHeight - y - 1)].red, number % 2);
        if (color == 'G')
            change_color(&bmp->color[x + bmp->info.biWidth * (bmp->info.biHeight - y - 1)].green, number % 2);
        number /= 2;
    }
}

int insert_message(picture* bmp, char* key_txt, char* msg_txt) {
    FILE* f_key = fopen(key_txt, "rt");
    if (f_key == NULL)
        return 1;
    FILE* f_msg = fopen(msg_txt, "rt");
    if (f_msg == NULL)
        return 1;    
    char letter = ' ';
    while (fscanf(f_msg, "%c", &letter) == 1 && letter != '\n') {
        if (letter == ' ')
            insert_letter(bmp, f_key, 26);
        if (letter == '.')
            insert_letter(bmp, f_key, 27);
        if (letter == ',')
            insert_letter(bmp, f_key, 28);
        if (letter >= 'A' && letter <= 'Z')
            insert_letter(bmp, f_key, letter - 'A');
    }
    fclose(f_msg);
    fclose(f_key);
    return 0;
}

int get_bit(int* number) {
    return (*number) % 2;
}

void extract_number(picture* bmp, FILE* f, int* number) {
    int x = 0, y = 0, pow = 1;
    *number = 0;
    char color = ' ';
    for (int i = 0; i < 5; i++) {
        if (fscanf(f, "%d%d%c%c", &x, &y, &color, &color) != 4) {
            *number = -1;
            return;
        }
        if (color == 'B')
            *number += pow * get_bit(&bmp->color[x + bmp->info.biWidth * (bmp->info.biHeight - y - 1)].blue);
        if (color == 'R')
            *number += pow * get_bit(&bmp->color[x + bmp->info.biWidth * (bmp->info.biHeight - y - 1)].red);
        if (color == 'G')
            *number += pow * get_bit(&bmp->color[x + bmp->info.biWidth * (bmp->info.biHeight - y - 1)].green);
        pow *= 2;
    }
}

int extract_message(picture* bmp, char* key_txt, char* msg_txt) {
    FILE* f_key = fopen(key_txt, "rt");
    if (f_key == NULL)
        return 1;
    FILE* f_msg = fopen(msg_txt, "wt");
    if (f_msg == NULL)
        return 1;    
    int number = 0;
    while (number != -1) {
        number = 1;
        extract_number(bmp, f_key, &number);
        if (number != -1) {
            if (number < 26)
                fprintf(f_msg, "%c", 'A' + number);
            if (number == 26)
                fprintf(f_msg, " ");
            if (number == 27)
                fprintf(f_msg, ".");
            if (number == 28)
                fprintf(f_msg, ",");
        }
    }
    fclose(f_msg);
    fclose(f_key);
    return 0;
}
