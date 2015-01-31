#ifndef HSV_MEANS_H
#define HSV_MEANS_H
#include <cstdio>
#include <cstdlib>
#include <climits>
#include "misc.h"
#include "image.h"
using namespace vlib;



namespace features {

int hsv_means(image<hsv_float>*, int, int, int, int, float*);

}
#endif
