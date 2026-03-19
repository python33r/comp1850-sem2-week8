#ifndef _PGM_PROCESS_H_
#define _PGM_PROCESS_H_

#include "pgm_image.h"

PGMImage* pgm_invert_colors(const PGMImage*);
PGMImage* pgm_rotate_image(const PGMImage*, int);

#endif   // _PGM_PROCESS_H_
