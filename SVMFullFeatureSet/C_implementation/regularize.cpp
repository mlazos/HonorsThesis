#include "regularize.h"
#include <limits>

using namespace std;

namespace regularization {


int regularize_col(double*,int,int,int,int);
int find_optimal_row(double*,int,int,int);
int find_optimal_row_disc(double*,int,int,int);

void regularize(double* labels, int rows, int cols) {
   

  for(int col = 0; col < cols; col++) {
    int row = find_optimal_row_disc(labels, rows,cols, col);
    regularize_col(labels, row, rows, cols, col); 
  }
  
}

int regularize_col(double *labels, int opt_row, int rows, int cols, int col) {

  for(int row = 0; row <= opt_row; row++) {
    labels[col + row * cols] = 0;
  }
  for(int row = opt_row + 1; row < rows; row++) { 
    labels[col + row * cols] = 1;
  }
  return 0;
}




int find_optimal_row_disc(double* labels, int rows, int cols, int col) {
  int  *num_ones = new int[rows];
  double sum = 0;
  for(int row = 0; row < rows; row++) {
    sum += labels[col + row*cols];
    num_ones[row] = sum;
  }


  int arg_min = -1;
  double min_score = 10000000;
  for(int row = 0; row < rows; row++) {
     double score_above = num_ones[row];
     double score_below = num_ones[rows - 1] - num_ones[row];
     double error = (rows - row) - score_below + score_above;
     if(error <= min_score) {
       arg_min = row;
       min_score = error;
     } 
  }

  delete num_ones;
  return arg_min;
}

int find_optimal_row(double* scores, int rows, int cols, int col) {
  double *ground_scores = new double[rows];
  double *not_ground_scores = new double[rows];

  double  ascend_sum = 0;
  double descend_sum = 0;
  for(int row = 0; row < rows; row++) {
    descend_sum += -1*scores[col + row * cols];
    not_ground_scores[row] = descend_sum;
    ascend_sum += scores[col + (rows - row - 1) * cols];
    ground_scores[rows - row - 1] = ascend_sum;
  }

  int arg_max = -1;
  double max_score = ground_scores[0];

  if(not_ground_scores[rows - 1] > max_score) {
    max_score = not_ground_scores[rows - 1];
    arg_max = rows - 1;
  }

  for(int row = 1; row < rows; row++) {
  	double score =  ground_scores[row] + not_ground_scores[row - 1];
    if(score >= max_score) {
      max_score = score;
      arg_max = row - 1;
    }
  }
  
  return 0;
}

}