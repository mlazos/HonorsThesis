#include "hsv_histograms.h"

using namespace vlib;

namespace features {


float hist_entropy(int, float*);


int hue_histogram_features(image<hsv_float>* image, int col_start, int col_end, int row_start, int row_end, float lower_bound, float upper_bound, int num_bins, float* hist) {

  float bin_size = (upper_bound - lower_bound)/num_bins;
  int total_pixels = (row_end - row_start) * (col_end - col_start);
  
  //generate histogram
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      hsv_float el = imRef(image, col, row);
      float hue = el.h;
      int ind = (int)floor((hue - lower_bound)/bin_size);
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



int sat_histogram_features(image<hsv_float>* image, int col_start, int col_end, int row_start, int row_end,  float lower_bound, float upper_bound, int num_bins, float* hist) {
  float bin_size = (upper_bound - lower_bound)/num_bins;
  int total_pixels = (row_end - row_start) * (col_end - col_start);
  
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      hsv_float el = imRef(image, col, row);
      float sat = el.s;
      int ind = (int)floor((sat - lower_bound)/bin_size);
      hist[ind] = hist[ind] + 1;
    }
  }

  //transform histogram
  float sum = 0;
  for(int ind = 0; ind < num_bins; ind++) {
    hist[ind] = (hist[ind] + .01)/(total_pixels + .03);
    sum = sum + hist[ind]; 
  }

  //normalize histogram
  for(int ind = 0; ind < num_bins; ind++) {
    hist[ind] = hist[ind]/sum;
  }  

  hist[num_bins] = hist_entropy(num_bins, hist);
}

float hist_entropy(int num_bins, float* hist) {
  float sum = 0;
  for(int ind = 0; ind < num_bins; ind++) {
    sum = sum +  hist[ind] * log(hist[ind]);
  }

  return -1*sum/log(num_bins);
}

}
