#include "hmm.h"
#include <limits>
#include <cmath>

#define PI  3.14159265358979323846


using namespace std;

namespace models {

int* labels_to_observables(double*,int,int);
double phi(int,int);
double x_cond_x(int,int);
double y_cond_x(double,int);


void most_likely_boundary(double* labels, int rows, int cols, matrix<float> t_probs ) {
   
  int *observables = labels_to_observables(labels, rows, cols);
  
  
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


double phi(int x_prev, int x, double y) {  

}

double x_cond_x(int x, int x_prev) {

}

double y_cond_x(int y, int x) {
	return gaussian_pdf((double)x, y, 1));
}

double gaussian_pdf(double x, double mean, double sigma) {
  return 1/(sigma*sqrt(2*PI))*exp(-.5*(x - mean)*(x - mean)/(sigma*sigma));
}


}
