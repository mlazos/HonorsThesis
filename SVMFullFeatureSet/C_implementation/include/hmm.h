#include <cstdio>
#include <cstdlib>
#include "matrix.h"


#ifndef HMM_H
#define HMM_H

using namespace vlib;

namespace models {


int *most_likely_boundary(double*,int,int);
//matrix<float> *read_transition_matrix();

}

#endif
