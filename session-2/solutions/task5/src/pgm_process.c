#include <stdio.h>
#include "pgm_process.h"

/**
 * @brief Inverts the colours of the image (255-value)
 *
 * @param image Pointer to original PGMImage
 * @return Pointer to new image with inverted colours
 */
PGMImage* pgm_invert_colors(const PGMImage* image) {
    /* Allocate memory for the inverted image */
    PGMImage* inverted_image = pgm_create_image(image->height, image->width, image->max_gray);
    if (inverted_image == NULL) {
        return NULL;
    }

    /* Invert each pixel (max_gray - value) */
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            inverted_image->data[i][j] = image->max_gray - image->data[i][j];
        }
    }

    return inverted_image;
}

/**
 * @brief Rotates the image by the specified angle
 *
 * @param original_image Pointer to original PGMImage
 * @param degrees Rotation angle (90, 180, or 270 degrees)
 * @return Pointer to new rotated image
 */
PGMImage* pgm_rotate_image(const PGMImage* image, int degrees) {
    PGMImage* rotated_image;

    switch (degrees) {
        case 90:
            /* For 90 degrees, width and height are swapped */
            rotated_image = pgm_create_image(image->width, image->height, image->max_gray);
            if (rotated_image == NULL) {
                return NULL;
            }

            /* 90 degree rotation algorithm */
            for (int i = 0; i < image->height; i++) {
                for (int j = 0; j < image->width; j++) {
                    rotated_image->data[j][image->height-1-i] = image->data[i][j];
                }
            }
            break;

        case 180:
            rotated_image = pgm_create_image(image->height, image->width, image->max_gray);
            if (rotated_image == NULL) {
                return NULL;
            }

            /* 180 degree rotation algorithm */
            for (int i = 0; i < image->height; i++) {
                for (int j = 0; j < image->width; j++) {
                    rotated_image->data[image->height-1-i][image->width-1-j] = image->data[i][j];
                }
            }
            break;

        case 270:
            /* For 270 degrees, width and height are swapped */
            rotated_image = pgm_create_image(image->width, image->height, image->max_gray);
            if (rotated_image == NULL) {
                return NULL;
            }

            /* 270 degree rotation algorithm */
            for (int i = 0; i < image->height; i++) {
                for (int j = 0; j < image->width; j++) {
                    rotated_image->data[image->width-1-j][i] = image->data[i][j];
                }
            }
            break;

        default:
            printf("Error: Invalid rotation angle\n");
            return NULL;
    }

    return rotated_image;
}
