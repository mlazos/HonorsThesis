#ifndef IO_H
#define IO_H

#include <cstdio>
#include <cstdlib>
#include <climits>
#include "pnmfile.h"
#include "hsv_conversion.h"
#include "hsv_means.h"
#include "hsv_histograms.h"
#include "location.h"
#include "imconv.h"
#include "canny.h"
#include "edge_centers.h"
#include "matrix.h"
#include "svm.h"
#include <math.h>
#include <dirent.h>

char** load_filenames(char*,int*);
void print_features(matrix<float>*,int,int,int,double*);
void create_highlighted_image(image<rgb>*,int,double*);
void color_tile(image<rgb>*,int,int,int,int);
void print_features(matrix<float>*,int,int,int,double*);

#endif
