#ifndef HSV_CONV_H
#define HSV_CONV_H
#include <cstdio>
#include <cstdlib>
#include <climits>
#include "image.h"
#include "misc.h"


using namespace vlib;

namespace hsv {

image<hsv_float> *rgb_to_hsv_im(image<rgb>*,image<float>**);
hsv_float rgb_to_hsv(const rgb);

}
#endif
