#include <cstdio>
#include <cstdlib>
#include <climits>
#include "image.h"
#include "misc.h"

#ifndef HSV_CONV_H
#define HSV_CONV_H

using namespace vlib;

namespace hsv {

image<hsv_float> *rgb_to_hsv_im(image<rgb>*);
hsv_float rgb_to_hsv(const rgb);

}
#endif
