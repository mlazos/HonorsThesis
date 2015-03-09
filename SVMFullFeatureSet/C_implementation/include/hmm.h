#include <cstdio>
#include <cstdlib>
#include "matrix.h"


#ifndef HMM_H
#define HMM_H

using namespace vlib;

namespace models {

matrix<float> *read_transition_matrix();

}

#endif
