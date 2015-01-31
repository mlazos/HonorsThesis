#ifndef EDGE_CENTERS_H
#define EDGE_CENTERS_H

#include <cstdio>
#include <cstdlib>
#include <climits>
#include "misc.h"
#include "image.h"

using namespace vlib;

namespace features {

int edge_centers(image<uchar>*, int, int, int, int, float*);

}
#endif
