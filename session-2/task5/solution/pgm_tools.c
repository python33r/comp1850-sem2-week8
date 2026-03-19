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
 * @brief Creates a PGMImage.
 * 
 * @param height Number of rows in the image
 * @param width Number of columns in the image
 * @param max_gray Maximum pixel value
 * @return Pointer to PGMImage structure, or NULL if allocation fails
 */
PGMImage* create_image(int height, int width, int max_gray) {
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
void free_image(PGMImage* image) {
    if (image == NULL) return;
    
    for (int i = 0; i < image->height; i++) {
        free(image->data[i]);
    }
    free(image->data);
    free(image);
}


/**
 * @brief Reads a PGM image from a file.
 * 
 * @param filename Path to the PGM file
 * @return Pointer to PGMImage structure, or NULL if reading fails
 */
PGMImage* read_pgm_image(const char *filename) {
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
    PGMImage* image = create_image(height, width, max_gray);
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
                free_image(image);
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
 * @brief Prints information about the PGM image
 * 
 * @param filename Name of the image file
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 */
void print_image_info(const char *filename, const PGMImage* image) {
    printf("Image: %s\n", filename);
    printf("Dimensions: %d x %d pixels\n", image->width, image->height);
    printf("Max Gray Value: %d\n", image->max_gray);
}


/**
 * @brief Prints the pixel values of the image
 * 
 * @param image PGMImage
 */
void print_image_values(const PGMImage* image) {
    printf("\nImage Pixel Values (%dx%d):\n", image->width, image->height);
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%3d ", image->data[i][j]);
        }
        printf("\n");
    }
}


/**
 * @brief Inverts the colours of the image (255-value)
 * 
 * @param image Pointer to original PGMImage
 * @return Pointer to new image with inverted colours
 */
PGMImage* invert_image_colors(const PGMImage* image) {
    /* Allocate memory for the inverted image */
    PGMImage* inverted_image = create_image(image->height, image->width, image->max_gray);
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
PGMImage* rotate_image(const PGMImage* image, int degrees) {
    PGMImage* rotated_image;

    switch (degrees) {
        case 90:
            /* For 90 degrees, width and height are swapped */
            rotated_image = create_image(image->width, image->height, image->max_gray);
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
            rotated_image = create_image(image->height, image->width, image->max_gray);
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
            rotated_image = create_image(image->width, image->height, image->max_gray);
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


/**
 * @brief Saves a PGM image to a file
 * 
 * @param filename Output filename
 * @param image Pointer to PGMImage to be saved
 * @return 1 if successful, 0 if failed
 */
int save_pgm_image(const char *filename, const PGMImage* image) {
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


int main(int argc, char **argv) {
    /* Check command line arguments */
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    /* Read the image */
    PGMImage* image = read_pgm_image(argv[1]);

    /* Check if image reading was successful */
    if (image == NULL) {
        return 1;
    }

    /* Display image information */
    print_image_info(argv[1], image);

    int choice = -1;
    char output_filename[100];
    int rotation_degrees;
    PGMImage* processed_image = NULL;

    /* Main program loop */
    do {
        choice = -1;
        display_menu();
        while (choice < 1)
            choice = get_user_menu_choice("Enter choice");

        switch (choice) {
        case 1: /* View image */
            print_image_values(image);
            break;

        case 2: /* Invert image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Inverting image colours...\n");
            processed_image = invert_image_colors(image);
            
            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */

            if (save_pgm_image(output_filename, processed_image)) {
                printf("Inverted image saved to %s\n", output_filename);
            } else {
                printf("Failed to save inverted image\n");
            }
            
            /* Free the processed image memory */
            free_image(processed_image);
            break;

        case 3: /* Rotate image */
            printf("Enter rotation in degrees (90, 180, or 270): ");
            scanf("%d", &rotation_degrees);
            getchar(); /* Consume newline */
            
            /* Validate rotation degrees */
            if (rotation_degrees != 90 && rotation_degrees != 180 && rotation_degrees != 270) {
                printf("Invalid rotation angle. Please use 90, 180, or 270 degrees.\n");
                break;
            }

            printf("Rotating image by %d degrees...\n", rotation_degrees);
            processed_image = rotate_image(image, rotation_degrees);

            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */

            if (save_pgm_image(output_filename, processed_image)) {
                printf("Rotated image saved to %s\n", output_filename);
            } else {
                printf("Failed to save rotated image\n");
            }

            free_image(processed_image);
            break;

        case 4: /* Quit */
            printf("Exiting program...\n");
            /* Free the original image memory before exiting */
            free_image(image);
            return 0;

        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    } while (1);
}

/**
 * @brief Gets user menu choice from standard input
 * 
 * @param message The prompt message to display
 * @return int The user's choice, or -1 if invalid input
 */
int get_user_menu_choice(const char *message) {
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

/**
 * @brief Displays the main program menu
 */
void display_menu(void) {
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}
