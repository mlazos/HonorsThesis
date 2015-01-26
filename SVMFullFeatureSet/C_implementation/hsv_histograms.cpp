#include <cstdio>
#include <cstdlib>
#include <climits>
#include <math.h>
#include "pnmfile.h"
#include "filter.h"

using namespace vlib;

namespace features {

int hue_histogram_features(image<hsv_float> image, int col_start, int col_end, int row_start, int row_end, float lower_bound, float upper_bound, int num_bins, float* hist) {
 

  float bin_size = (upper_bound - lower_bound)/num_bins + lower_bound;
  int total = (col_end - col_start) + (row_end - row_start);

  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      hsv_float el = imRef(image, col, row);
      float hue = el.h;
      int ind = (int)floor((hue - lower_bound)/bin_size);
      hist[ind] = hist[ind] + (1.0/((float)total + .05));
    }
  }
 
  float sum = 0;
  for(int ind = 0; ind < num_bins; ind++) {
    sum = sum +  hist[ind] * log(hist[ind]);
  }

  hist[num_bins + 1] = -1*sum/log(num_bins);


}



int sat_histogram_features(image<hsv_float> im, int col_start, int col_end, int row_start, int row_end,  float lower_bound, float upper_bound, int num_bins, float* hist) {
  float bin_size = (upper_bound - lower_bound)/num_bins + lower_bound;
  int total = (col_end - col_start) + (row_end - row_start);

  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      hsv_float el = imRef(image, col, row);
      float hue = el.h;
      int ind = (int)floor((sat - lower_bound)/bin_size);
      hist[ind] = hist[ind] + (1.0/((float)total + .03));
       

    }
  }
  
  float sum = 0;
  for(int ind = 0; ind < num_bins; ind++) {
    sum = sum +  hist[ind] * log(hist[ind]);
  }

  hist[num_bins + 1] = -1*sum/log(num_bins);




}


float sum_hist(float* hist, int num_bins) {
  float sum = 0;

  for(int ind = 0; ind < num_bins; ind++){
    sum = sum + hist[ind];
  }    

  return sum;
}

}
