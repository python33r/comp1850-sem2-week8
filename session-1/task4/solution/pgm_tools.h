#ifndef _PGM_TOOLS_H_
#define _PGM_TOOLS_H_

typedef struct {
    int width;
    int height;
    int max_gray;
    unsigned char** data;
} PGMImage;

/* Function prototypes */
PGMImage* allocate_image(int, int);
void free_image(PGMImage*);
PGMImage* read_pgm_image(const char*);
void print_image_info(const char*, const PGMImage*);
void print_image_values(const PGMImage*);
PGMImage* invert_image_colors(const PGMImage*);
PGMImage* rotate_image(const PGMImage*, int);
int save_pgm_image(const char*, const PGMImage*);
int get_user_menu_choice(const char*);
void display_menu(void);

#endif  // _PGM_TOOLS_H_
