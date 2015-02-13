

#ifndef TEXT_H
#define TEXT_H

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <math.h>
#include "pnmfile.h"
#include "misc.h"
#include "image.h"

using namespace vlib;

namespace features {

int gray_histogram_features(image<float>*, int, int, int, int, float, float, int, float*);
int gray_variance(image<float>*, int, int, int, int, float*);
}
#endif
