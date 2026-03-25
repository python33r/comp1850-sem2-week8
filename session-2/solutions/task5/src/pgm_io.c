#include <stdio.h>
#include <string.h>
#include "pgm_io.h"

/**
 * @brief Reads a PGM image from a file.
 *
 * @param filename Path to the PGM file
 * @return Pointer to PGMImage structure, or NULL if reading fails
 */
PGMImage* pgm_read_image(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    /* Read PGM header */
    char magic_number[3];
    if (fscanf(file, "%2s", magic_number) != 1) {
        printf("Error: Invalid PGM file format\n");
        fclose(file);
        return NULL;
    }

    if (strcmp(magic_number, "P2") != 0) {
        printf("Error: File is not a valid PGM file (P2 format)\n");
        fclose(file);
        return NULL;
    }

    int width, height;
    if (fscanf(file, "%d %d", &width, &height) != 2) {
        printf("Error: Could not read image dimensions\n");
        fclose(file);
        return NULL;
    }

    int max_gray;
    if (fscanf(file, "%d", &max_gray) != 1) {
        printf("Error: Could not read max gray value\n");
        fclose(file);
        return NULL;
    }

    /* Allocate memory for image */
    PGMImage* image = pgm_create_image(height, width, max_gray);
    if (image == NULL) {
        fclose(file);
        return NULL;
    }

    /* Read pixel values */
    int pixel_value;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (fscanf(file, "%d", &pixel_value) != 1) {
                printf("Error: Could not read pixel value at position (%d,%d)\n", j, i);
                pgm_free_image(image);
                fclose(file);
                return NULL;
            }
            image->data[i][j] = (unsigned char) pixel_value;
        }
    }

    fclose(file);
    return image;
}

/**
 * @brief Saves a PGM image to a file
 *
 * @param filename Output filename
 * @param image Pointer to PGMImage to be saved
 * @return 1 if successful, 0 if failed
 */
int pgm_save_image(const char *filename, const PGMImage* image) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", filename);
        return 0;
    }

    /* Write PGM header */
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->max_gray);

    /* Write pixel values */
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fprintf(file, "%d ", image->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 1;
}
