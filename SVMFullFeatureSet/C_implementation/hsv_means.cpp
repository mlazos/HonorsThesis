#include "hsv_means.h"

using namespace vlib;

namespace features {


/*Calculates the mean hsv values in the square defined by (col_start, col_end), (row_start, row_end)*/
int hsv_means(image<hsv_float>* image, int col_start, int col_end, int row_start, int row_end, float* result) {

  hsv_float avg;
  avg.h = 0;
  avg.s = 0;
  avg.v = 0;
  int rows = row_end - row_start;
  int cols = col_end - col_start;
  int total = rows * cols;

  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
       avg = avg + imRef(image, col, row);  
    }
  }


   avg.h = avg.h/total;
  avg.s = avg.s/total;
  avg.v = avg.v/total;

  result[0] = avg.h;
  result[1] = avg.s;
  result[2] = avg.v;

  return 0;
}

}


