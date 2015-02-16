#include "edge_centers.h"

using namespace vlib;

namespace features {

int edginess(image<uchar>* image, int col_start, int col_end, int row_start, int row_end, float* edginess) {
  
  float sum = 0;
  float num_pix = (col_end - col_start) * (row_end - row_start);

  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      sum += imRef(image,col, row);
    }
  }
  

  *edginess = sum/num_pix;

  return 0;

}



}
