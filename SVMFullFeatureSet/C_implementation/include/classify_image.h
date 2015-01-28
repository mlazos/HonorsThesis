#include <cstdio>
#include <cstdlib>
#include <climits>
#include "pnmfile.h"
#include "hsv_conversion.h"
#include "hsv_means.h"
#include "hsv_histograms.h"
#include "location.h"
#include "imconv.h"
#include "filter.h"
#include "canny.h"
#include "edge_centers.h"
#include "matrix.h"
#include "svm.h"
#include <math.h>

svm_problem *convert_features(matrix<float>*);
