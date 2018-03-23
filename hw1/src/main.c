#include <bmp.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    picture bmp;
    picture* p_bmp = &bmp;
    if (strcmp(argv[1], "crop-rotate") == 0) {
        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int width = atoi(argv[6]);
        int height = atoi(argv[7]);
        if (load_bmp(argv[2], p_bmp) == 1)
            return 1;
        if (crop(p_bmp, x, y, width, height) == 1)
            return 2;
        if (rotate(p_bmp) == 1)
            return 3;
        if (save_bmp(argv[3], p_bmp) == 1)
            return 4;
        free(p_bmp->color);
    }
    if (strcmp(argv[1], "insert") == 0) {
        if (load_bmp(argv[2], p_bmp) == 1)
            return 1;
        if (insert_message(p_bmp, argv[4], argv[5]) == 1)
            return 2;
        if (save_bmp(argv[3], p_bmp)== 1)
            return 4;
        free(p_bmp->color);
    }
    if (strcmp(argv[1], "extract") == 0) {
        if (load_bmp(argv[2], p_bmp) == 1)
            return 1;
        if (extract_message(p_bmp, argv[3], argv[4]) == 1)
            return 2;
        free(p_bmp->color);
    }
    return 0;
}
