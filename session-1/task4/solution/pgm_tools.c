/**
 * @file activity3-pgm_tools_refactored.c
 * @brief Tools for manipulating PGM (Portable Gray Map) image files
 * 
 * COMP1850 Structures Task 3 solution
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm_tools.h"


/**
 * @brief Allocates space for a PGMImage.
 * 
 * @param height Number of rows in the image
 * @param width Number of columns in the image
 * @return PGMImage struct, or NULL if allocation fails
 */
PGMImage* allocate_image(int height, int width) {
    PGMImage* image = (PGMImage*) malloc(sizeof(PGMImage));
    if (image == NULL) {
        printf("Error: Memory allocation failed for PGMImage struct\n");
        return NULL;
    }
    
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
void free_image(PGMImage* image) {
    if (image == NULL) return;
    
    for (int i = 0; i < image->height; i++) {
        free(image->data[i]);
    }
    free(image->data);
    free(image);
}


// etc...
