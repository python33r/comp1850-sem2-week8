#include <stdio.h>
#include "pgm_display.h"

/**
 * @brief Prints information about the PGM image
 *
 * @param filename Name of the image file
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 */
void pgm_print_info(const char *filename, const PGMImage* image) {
    printf("Image: %s\n", filename);
    printf("Dimensions: %d x %d pixels\n", image->width, image->height);
    printf("Max Gray Value: %d\n", image->max_gray);
}

/**
 * @brief Prints the pixel values of the image
 *
 * @param image PGMImage
 */
void pgm_print_pixels(const PGMImage* image) {
    printf("\nImage Pixel Values (%dx%d):\n", image->width, image->height);
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%3d ", image->data[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Displays the main program menu
 */
void pgm_display_menu(void) {
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}

/**
 * @brief Gets user menu choice from standard input
 *
 * @param message The prompt message to display
 * @return int The user's choice, or -1 if invalid input
 */
int pgm_get_user_choice(const char *message) {
    char buffer[100];
    int choice;
    printf("%s: ", message);
    fgets(buffer, 100, stdin);
    int check = sscanf(buffer, "%d", &choice);
    if (!check) {
        return -1;
    }
    return choice;
}
