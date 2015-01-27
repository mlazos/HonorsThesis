#include <cstdio>
#include <cstdlib>
#include <climits>
#include "pnmfile.h"
#include "hsv_conversion.h"
#include "hsv_means.h"
#include "hsv_histograms.h"
#include "location.h"
#include "imconv.h"
#include "filter.h"
#include "canny.h"
#include "edge_centers.h"
#include "matrix.h"
#include <math.h>

using namespace vlib;
using namespace hsv;
using namespace features;
int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "usage: %s input(ppm) output(ppm) sigma\n", argv[0]);
    return 1;
  }

  char *input_name = argv[1];
  char *output_name = argv[2];
  double sigma = atof(argv[3]);

  // load input
  image<rgb> *input = loadPPM(input_name); 
  image<hsv_float> *hsv_im = rgb_to_hsv_im(input);
  image<uchar> *gray = imageRGBtoGRAY(input);
  image<float> *smoothed = smooth(gray, 1.0);
  image<uchar> *edgeim = canny(smoothed, 1.0);
  
  const int tile_size = 30;
  int width = hsv_im->width();
  int height = hsv_im->height();
  
  int num_tiles = (width/tile_size) * (height/tile_size);

  matrix<float>* features = new matrix<float>(num_tiles, 16, true);
  int num_features = 0;
  //calcualte features over all tiles
  for(int row = 0; row + tile_size < height; row += tile_size) {
    for(int col = 0; col + tile_size < width; col += tile_size) {
      hsv_means(hsv_im, col, col + tile_size, row, row + tile_size, matPtr(features, num_features, 0));
      hue_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, 5, matPtr(features, num_features, 3)); 
      sat_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, 3, matPtr(features, num_features, 9)); 
      location_features(row, row + tile_size, input->height(), matPtr(features, num_features, 13));
      edge_centers(edgeim, col, col + tile_size, row, row + tile_size, matPtr(features,num_features, 14));          

      for(int ind = 0; ind < 16; ind++) {
        printf("%f ", matRef(features, num_features, ind));
      } 
      printf("\n");

      num_features++;
    }
  }


  

  delete input;
  delete smoothed;
  delete gray;
}
