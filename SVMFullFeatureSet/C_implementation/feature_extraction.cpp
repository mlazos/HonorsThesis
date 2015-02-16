#include "feature_extraction.h"
#include "filter.h"
#include "grad.h"

using namespace vlib;
using namespace hsv;
using namespace features;


int compute_labels(image<uchar> *truth, int tile_size, int init_row, double *labels) {
  int width = truth->width();
  int height = truth->height();

  int num_labels = init_row;
  for(int row = 0; row + tile_size < height; row += tile_size) {
    for(int col = 0; col + tile_size < width; col += tile_size) {
	  compute_label(truth, col, col + tile_size, row, row + tile_size, &(labels[num_labels]));  
	  num_labels++;
    }
  }
  
  return num_labels;

}



int compute_label(image<uchar> *truth, int col_start, int col_end, int row_start, int row_end, double *label) {
  int sum = 0;
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      sum = sum + (1 - imRef(truth, col, row));
	  }
  }
  int total = (row_end - row_start) * (col_end - col_start);
  if((float)(sum/total) > .9) {
    *label = 1.0;
  }
  else {
  	*label = 0.0;
  }
  return 0;
}


/*
  compute features
  fills in features starting at init_row
  returns number of feature vectors (rows) added
*/
int compute_features(image<rgb> *input, int tile_size, int init_row,  matrix<float>* features) {
  image<hsv_float> *hsv_im = rgb_to_hsv_im(input);
  image<uchar> *gray = imageRGBtoGRAY(input);
  image<float> *gray_f = imageUCHARtoFLOAT(gray);
  image<float> *smoothed = smooth(gray, 1.0);
  image<uchar> *edgeim = canny(smoothed, 1.0);
  image<float> *dx,*dy,*mag;
  gradient(gray_f,&dx,&dy,&mag);
  int width = hsv_im->width();
  int height = hsv_im->height();

  
  int num_features = init_row;
  
  //calculate features over all tiles
  for(int row = 0; row + tile_size < height; row += tile_size) {
    for(int col = 0; col + tile_size < width; col += tile_size) {
      hsv_means(hsv_im, col, col + tile_size, row, row + tile_size, matPtr(features, num_features, 0));
      hue_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, NUM_H_BINS, matPtr(features, num_features, NUM_MEANS)); 
      sat_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, NUM_S_BINS, matPtr(features, num_features, NUM_MEANS + NUM_H_BINS + 1)); 
      gray_variance(gray_f, col, col + tile_size, row, row + tile_size, matPtr(features, num_features, NUM_MEANS + NUM_H_BINS + NUM_S_BINS + 2));
      edginess(edgeim, col, col + tile_size, row, row + tile_size, matPtr(features, num_features, NUM_MEANS + NUM_H_BINS + NUM_S_BINS + NUM_VAR + 2));
      location_features(row, row + tile_size, input->height(), matPtr(features, num_features,  NUM_MEANS + NUM_H_BINS + NUM_S_BINS + NUM_VAR + NUM_EDGE + 2));
      gradient_histogram(mag,dx,dy, col, col + tile_size, row, row + tile_size, NUM_G_BINS, matPtr(features, num_features,  NUM_MEANS + NUM_H_BINS + NUM_S_BINS + NUM_VAR + NUM_EDGE +  NUM_LOC + 2));
      num_features++;
    }
  }
  delete hsv_im;
  delete gray_f;
  delete gray; 
  delete edgeim;
  delete smoothed;
  return num_features; 

}

svm_problem *convert_features(matrix<float> *features, double *labels) {
  int width = features->cols();
  int height = features->rows();
  svm_problem *prob = new svm_problem; 
  svm_node **nodes = new svm_node*[features->rows()];

  for(int row = 0; row < height; row++) {

    //count number of non-zero elements for allocation
    int num_els = 0;
    for(int col = 0; col < width; col++) {
      if(matRef(features, row, col) != 0) {
        num_els++;
      }
    }
    //create sparse representation
    svm_node *vec = new svm_node[num_els + 1];
    num_els = 0;
    for(int col = 0; col < width; col++) {
      if(matRef(features, row, col) != 0) {
        vec[num_els].value = matRef(features, row, col);
        vec[num_els].index = col + 1;
        num_els++;
      }
    }
    vec[num_els].index = -1;   
    nodes[row] = vec;
  }

  prob->x = nodes;
  prob->y = labels;
  prob->l = height;

  return prob;
}





