#ifndef CLASSIFY_IMAGE_H
#define CLASSIFY_IMAGE_H
#include <cstdio>
#include <cstdlib>
#include "pnmfile.h"
#include "svm.h"
#include <math.h>
#include "feature_extraction.h"

void create_highlighted_image(image<rgb>*,int,double*);
void color_tile(image<rgb>*,int,int,int,int);
#endif
