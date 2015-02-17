#ifndef FEATURE_EXTRACTION_H
#define FEATURE_EXTRACTION_H

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
#include "textures.h"
#include "matrix.h"
#include "svm.h"
#include <math.h>
#include <dirent.h>
#include "edginess.h"

#define NUM_MEANS  3
#define NUM_H_BINS  5
#define NUM_S_BINS  5
#define NUM_G_BINS  8
#define NUM_VAR  1
#define NUM_LOC  1
#define NUM_EDGE  1
 
#define TILE_DIM 30
//add 3 for each of the histogram entropy features
#define NUM_FEATURES (NUM_MEANS + NUM_H_BINS + NUM_S_BINS + 2*NUM_G_BINS + NUM_VAR + NUM_LOC + NUM_EDGE + 3)

int compute_labels(image<uchar>*, int, int, double*);
int compute_label(image<uchar>*, int, int, int, int, double*);
int compute_features(image<rgb>*,int,int,matrix<float>*);
char** load_filenames(char*,int*);
void print_features(matrix<float>*,int,int,int,double*);
svm_problem *convert_features(matrix<float>*,double*);
#endif
