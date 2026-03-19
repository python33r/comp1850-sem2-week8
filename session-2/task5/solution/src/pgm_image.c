#include <stdio.h>
#include <stdlib.h>
#include "pgm_image.h"

/**
 * @brief Creates a PGMImage.
 *
 * @param height Number of rows in the image
 * @param width Number of columns in the image
 * @param max_gray Maximum pixel value
 * @return Pointer to PGMImage structure, or NULL if allocation fails
 */
PGMImage* pgm_create_image(int height, int width, int max_gray) {
    PGMImage* image = (PGMImage*) malloc(sizeof(PGMImage));
    if (image == NULL) {
        printf("Error: Memory allocation failed for PGMImage struct\n");
        return NULL;
    }

    image->width = width;
    image->height = height;
    image->max_gray = max_gray;

    image->data = calloc(height, sizeof(unsigned char *));
    if (image->data == NULL) {
        printf("Error: Memory allocation failed for pixel data\n");
        free(image);
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        image->data[i] = calloc(width, sizeof(unsigned char));
        if (image->data[i] == NULL) {
            printf("Error: Memory allocation failed for image row %d\n", i);

            for (int j = 0; j < i; j++) {
                free(image->data[j]);
            }
            free(image->data);
            free(image);

            return NULL;
        }
    }

    return image;
}

/**
 * @brief Frees memory allocated for a PGMImage.
 *
 * @param image The PGMImage struct to be freed
 */
void pgm_free_image(PGMImage* image) {
    if (image == NULL) return;

    for (int i = 0; i < image->height; i++) {
        free(image->data[i]);
    }
    free(image->data);
    free(image);
}
