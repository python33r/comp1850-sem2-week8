#ifndef _PGM_DISPLAY_H_
#define _PGM_DISPLAY_H_

#include "pgm_image.h"

void pgm_print_info(const char*, const PGMImage*);
void pgm_print_pixels(const PGMImage*);
void pgm_display_menu(void);
int pgm_get_user_choice(const char*);

#endif   // _PGM_DISPLAY_H_
