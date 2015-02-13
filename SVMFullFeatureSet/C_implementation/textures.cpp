#include "textures.h"

using namespace vlib;

namespace features {


float hist_entropy(int,float*);


int gray_histogram_features(image<float>* image, int col_start, int col_end, int row_start, int row_end, float lower_bound, float upper_bound, int num_bins, float* hist) {

  float bin_size = (upper_bound - lower_bound)/num_bins;
  int total_pixels = (row_end - row_start) * (col_end - col_start);
  //generate histogram
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      float el = imRef(image, col, row);
      int ind = (int)floor((el - lower_bound)/bin_size);
      hist[ind] = hist[ind] + 1;
    }
  }

  
  //transform histogram
  float sum = 0;
  for(int ind = 0; ind < num_bins; ind++) {
    hist[ind] = (hist[ind] + .01)/(total_pixels + .05);
    sum = sum + hist[ind]; 
  }

  //normalize histogram
  for(int ind = 0; ind < num_bins; ind++) {
    hist[ind] = hist[ind]/sum;
  }  

  hist[num_bins] = hist_entropy(num_bins, hist);
  return 0;
}

int gray_variance(image<float>* image, int col_start, int col_end, int row_start, int row_end, float* var) {
  

  float total_pixels = (row_end - row_start) * (col_end - col_start);
  float sum = 0;
  for(int row = row_start; row < row_end; row++) {
   for(int col = col_start; col < col_end; col++) {
      float el = imRef(image, col, row)/255;
      sum += el;    
    }
  }
  
  float mean = sum/total_pixels;
  
  float accum = 0;
  for(int row = row_start; row < row_end; row++) {
   for(int col = col_start; col < col_end; col++) {
      float el = imRef(image, col, row)/255;
      accum += (el - mean) * (el - mean);    
    }
  }
  
  *var = accum/total_pixels;

  return 0;

}


}
