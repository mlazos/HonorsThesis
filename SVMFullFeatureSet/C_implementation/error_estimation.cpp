#include "regularize.h"
#include <limits>
#include "hmm.h"
#include <math.h>
#include "error_estimation.h"

using namespace std;
using namespace models;

namespace regularization {

#define HIST_SIZE 20
static float score_hist[HIST_SIZE];
static float score_totals[HIST_SIZE];
float bin_size = .5;    	
int lower_bound = -5;
int upper_bound = 5;
int upper_ind_bound = (upper_bound + abs(lower_bound))/bin_size - 1;

void update_score_hist(int len, double* score, double* labels) {
	for(int row = 0; row < len; row++) {
	 	   double s = score[row] + abs(lower_bound);		
		   int ind = (int)floor(s/bin_size);
		   if(ind > upper_ind_bound) {
	   	     ind = upper_ind_bound;
		   } else if(ind < 0) {
		   	 ind = 0;
		   }

           score_hist[ind] = score_hist[ind] + labels[row];
    	   score_totals[ind] = score_totals[ind] + 1;
	}
}

float prob_ground_given_score(double score) {
	int ind = (int)floor((score + abs(lower_bound))/bin_size);
	if(ind > upper_ind_bound) {
			ind = upper_ind_bound;
	}
	else if(ind < 0) {
			ind = 0;
	}
	return score_hist[ind]/score_totals[ind];
}

float prob_not_ground_given_score(double score) {
	return 1 - prob_ground_given_score(score);
}


void print_histogram() {
	for(int ind = 0; ind < HIST_SIZE; ind++) {
		printf("%f ", score_hist[ind]/score_totals[ind]);
	}
	printf("\n");
}

}
