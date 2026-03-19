#include <stdio.h>
#include "pgm_io.h"
#include "pgm_display.h"
#include "pgm_process.h"

int main(int argc, char **argv) {
    /* Check command line arguments */
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    /* Read the image */
    PGMImage* image = pgm_read_image(argv[1]);

    /* Check if image reading was successful */
    if (image == NULL) {
        return 1;
    }

    /* Display image information */
    pgm_print_info(argv[1], image);

    int choice = -1;
    char output_filename[100];
    int rotation_degrees;
    PGMImage* processed_image = NULL;

    /* Main program loop */
    do {
        choice = -1;
        pgm_display_menu();
        while (choice < 1)
            choice = pgm_get_user_choice("Enter choice");

        switch (choice) {
        case 1: /* View image */
            pgm_print_pixels(image);
            break;

        case 2: /* Invert image */
            printf("Inverting image colours...\n");
            processed_image = pgm_invert_colors(image);

            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */

            if (pgm_save_image(output_filename, processed_image)) {
                printf("Inverted image saved to %s\n", output_filename);
            } else {
                printf("Failed to save inverted image\n");
            }

            /* Free the processed image memory */
            pgm_free_image(processed_image);
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
            processed_image = pgm_rotate_image(image, rotation_degrees);

            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */

            if (pgm_save_image(output_filename, processed_image)) {
                printf("Rotated image saved to %s\n", output_filename);
            } else {
                printf("Failed to save rotated image\n");
            }

            pgm_free_image(processed_image);
            break;

        case 4: /* Quit */
            printf("Exiting program...\n");
            /* Free the original image memory before exiting */
            pgm_free_image(image);
            return 0;

        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    } while (1);
}
