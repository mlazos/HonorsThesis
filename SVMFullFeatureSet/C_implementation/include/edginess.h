#ifndef EDGE_H
#define EDGE_H

#include <cstdio>
#include <cstdlib>
#include <climits>
#include "misc.h"
#include "image.h"

using namespace vlib;

namespace features {

int edginess(image<uchar>*, int, int, int, int, float*);

}
#endif
