#include "regularize.h"
#include <limits>
#include "hmm.h"
#include <math.h>
#include "error_estimation.h"

using namespace std;
using namespace models;

namespace regularization {

int regularize_col(double*,int,int,int,int);
int find_optimal_row(double*,int,int,int);
int find_optimal_row_disc(double*,int,int,int);
int find_optimal_row_p(double*,int,int,int);


void regularize(double* labels, int rows, int cols) {
  for(int col = 0; col < cols; col++) {
    int row = find_optimal_row(labels, rows,cols, col);
    regularize_col(labels, row, rows, cols, col); 
  }

  
  int *states = most_likely_boundary(labels, rows, cols);
 
  for(int col = 0; col < cols; col++) {
     regularize_col(labels, states[col], rows, cols, col);
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


/*Uses SVM labels to find optimal row*/
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

/*Uses SVM scores to find optimal row*/
int find_optimal_row(double* scores, int rows, int cols, int col) {
  double *ground_scores = new double[rows];
  double *not_ground_scores = new double[rows];

  double  ascend_sum = 0;
  double descend_sum = 0;
  for(int row = 0; row < rows; row++) {
    descend_sum += scores[col + row * cols];
    not_ground_scores[row] = descend_sum;
    ascend_sum += -1*scores[col + (rows - row - 1) * cols];
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
  
  return arg_max;
}

/*Uses probability estimate*/
int find_optimal_row_p(double* scores, int rows, int cols, int col) {
  double *ground_scores = new double[rows];
  double *not_ground_scores = new double[rows];

  double  ascend_prod = 1;
  double descend_prod = 1;
  for(int row = 0; row < rows; row++) {
    descend_prod = descend_prod * prob_not_ground_given_score( scores[col + row * cols]);
    not_ground_scores[row] = descend_prod;
    ascend_prod = ascend_prod * prob_ground_given_score(scores[col + (rows - row - 1) * cols]);
    ground_scores[rows - row - 1] = ascend_prod;
  }

  int arg_max = -1;
  double max_score = -100000000000;

  if(not_ground_scores[rows - 1] > max_score) {
    max_score = not_ground_scores[rows - 1];
    arg_max = rows - 1;
  }

  for(int row = 1; row < rows; row++) {
  	double score =  ground_scores[row] * not_ground_scores[row - 1];
    if(score >= max_score) {
      max_score = score;
      arg_max = row - 1;
    }
  }
  return arg_max;
}




}
