#include <cstdio>
#include <cstdlib>
#include <climits>
#include "pnmfile.h"
#include "filter.h"

namespace features {

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "usage: %s input(ppm) output(ppm) sigma\n", argv[0]);
    return 1;
  }

  char *input_name = argv[1];
  char *output_name = argv[2];
  double sigma = atof(argv[3]);

  // load input
  image<uchar> *input = loadPPM(input_name);

  // convolve image with gaussian
  image<float> *smoothed = smooth(input, sigma);

  // convert to gray
  image<uchar> *output = imageFLOATtoUCHAR(smoothed, 0, UCHAR_MAX);

  // save output
  savePPM(output, output_name);

  delete input;
  delete output;
}

}
