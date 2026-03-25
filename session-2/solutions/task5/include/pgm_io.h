#ifndef _PGM_IO_H_
#define _PGM_IO_H_

#include "pgm_image.h"

PGMImage* pgm_read_image(const char*);
int pgm_save_image(const char*, const PGMImage*);

#endif   // _PGM_IO_H_
