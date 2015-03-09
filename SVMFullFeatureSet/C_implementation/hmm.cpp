#include "hmm.h"
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "matrix.h"

#define PI  3.14159265358979323846


using namespace std;
using namespace vlib;

namespace models {

int* labels_to_observables(double*,int,int);
double phi(int,int);
double x_cond_x(int,int);
double y_cond_x(int,int);
matrix<float> *read_transition_matrix();
double gaussian_pdf(double,double,double);



static matrix<float> *transition_mat = NULL;


void most_likely_boundary(double* labels, int rows, int cols) {

  const int NUM_LATENT = cols;
  const int NUM_STATES = rows;
   
  int *observables = labels_to_observables(labels, rows, cols);
  transition_mat = read_transition_matrix();

  matrix<float> *max_table = new matrix<float>(NUM_LATENT, NUM_STATES);
  matrix<int> *r_table = new matrix<int>(NUM_LATENT, NUM_STATES);
   

  /* Initial iteration */
  /* iterate through values of x1, finding the maximal x0 */
  for(int x1 = 0; x1 < NUM_STATES; x1++) {
    
    /* determine maximal x1 */
    float max_prob = -10000000;
    int arg_max = -1;
    for(int x0 = 0; x0 < NUM_STATES; x0++) {
      float value = log(phi1(x0,x1,observables[0],observables[1]));
      if(value > max_prob) {
        max_prob = value;
        arg_max = x0;
      }  
    }
    
    matRef(max_table, 0, x1) = max_prob;
    matRef(r_table, 0, x1) = arg_max;
  }


  for(int node = 1; node < NUM_LATENT; node++) {
    

    for(int x = 0; x < NUM_STATES; x++) {
      
      /*determine maximal x_prev using stored values*/
      float max_prob = -10000000;
      int arg_max = -1;
      for(int x_prev = 0; x_prev < NUM_STATES; x_prev++) {
        float value = log(phi(x_prev, x, observables[node])) + matRef(max_table, node - 1, x_prev);
        if(value > max_prob) {
          max_prob = value;
 		  arg_max = x_prev;
        }
      }
      
	  matRef(max_table, node, x) = max_prob;
      matRef(r_table, node, x) = arg_max;
      
    }


  }

  float max_prob = -1000000;
  int arg_max = -1;
  for(int i = 0; i < NUM_STATES; i++) {
    float value = matRef(max_table, NUM_LATENT - 1, i);
    if( value > max_prob) {
      max_prob = value;
      arg_max = i;
    }
  }
  
  int prev_col = arg_max;
  
  int *final_states = new int[NUM_LATENT];

  for(int i = NUM_LATENT - 1; i > -1; i--) {
    final_states[i] = matRef(r_table, i, prev_col);
    prev_col = final_states[i];
  }
 
    
}





int* labels_to_observables(double* labels, int rows, int cols) {
	int* observables = new int[cols];

    for(int row = 0; row < rows; row++) {
      for(int col = 0; col < cols; col++) {
        observables[col] += labels[col + row*cols];
  	  }
    }

	return observables;
}

double phi1(int x1, int x2, int y1, int y2) {
  return x_cond_x(x2, x1) * y_cond_x(y1, x1) * y_cond_x(y2, x2);
}

double phi(int x_prev, int x, int y) {  
  return x_cond_x(x, x_prev) * y_cond_x(y, x);
}

double x_cond_x(int x, int x_prev) {
  return matRef(transition_mat, x, x_prev);  
}

double y_cond_x(int y, int x) {
	return gaussian_pdf((double)x, y, 1);
}

double gaussian_pdf(double x, double mean, double sigma) {
  return 1/(sigma*sqrt(2*PI))*exp(-.5*(x - mean)*(x - mean)/(sigma*sigma));
}

matrix<float> *read_transition_matrix() {

  FILE *ptr_file;
  char buf[30];

  ptr_file =fopen("transition_matrix.txt","r");
  if (!ptr_file)
    return NULL;

  matrix<float> *transition = new matrix<float>(20,20, true);

    
  for(int row = 0; row < 20; row++) {
    for(int col = 0; col < 20; col++) {
      fgets(buf, 30, ptr_file);
      matRef(transition, row, col) = atof(buf); 
    }
  }

  fclose(ptr_file);
  return transition;

}

}
