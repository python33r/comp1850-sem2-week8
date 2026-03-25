#ifndef _PGM_IMAGE_H_
#define _PGM_IMAGE_H_

typedef struct {
    int width;
    int height;
    int max_gray;
    unsigned char** data;
} PGMImage;

PGMImage* pgm_create_image(int, int, int);
void pgm_free_image(PGMImage*);

#endif   // _PGM_IMAGE_H_
