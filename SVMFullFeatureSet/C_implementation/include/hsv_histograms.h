#include <cstdio>
#include <cstdlib>
#include <climits>
#include <math.h>
#include "pnmfile.h"
#include "misc.h"
#include "image.h"

using namespace vlib;

#ifndef HSV_HIST_H
#define HSV_HIST_H
namespace features {
int hue_histogram_features(image<hsv_float>*, int, int, int, int, float, float, int, float*);
int sat_histogram_features(image<hsv_float>*, int, int, int, int, float, float, int, float*); 
}
#endif
