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
#include "matrix.h"
#include "svm.h"
#include <math.h>
#include <dirent.h>

int compute_labels(image<uchar>*, int, int, double*);
int compute_label(image<uchar>*, int, int, int, int, double*);
int compute_features(image<rgb>*,int,int,matrix<float>*);
char** load_filenames(char*,int*);
void print_features(matrix<float>*,int,int,int,double*);
svm_problem *convert_features(matrix<float>*,double*);
#endif
