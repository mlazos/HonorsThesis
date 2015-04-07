#include <cstdio>
#include <cstdlib>

#ifndef ERRE_H
#define ERRE_H

namespace regularization {
float prob_ground_given_score(double);
float prob_not_ground_given_score(double);
void update_score_hist(int,double*,double*);
void print_histogram();
}

#endif
