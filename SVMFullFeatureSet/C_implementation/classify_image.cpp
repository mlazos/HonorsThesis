#include <cstdio>
#include <cstdlib>
#include <climits>
#include "pnmfile.h"
#include "hsv_conversion.h"
#include "hsv_means.h"
#include "hsv_histograms.h"
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

  const int tile_size = 30;
  int width = hsv_im->width();
  int height = hsv_im->height();
  
  int num_tiles = (width/tile_size) * (height/tile_size);
  float test[6];


  //calcualte features over all tiles
  for(int row = 0; row + tile_size < height; row += tile_size) {
    for(int col = 0; col + tile_size < width; col += tile_size) {
      //hsv_means(hsv_im, col, col + tile_size, row, row + tile_size, test);
      //hue_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, 5, test); 
      //sat_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, 3, test); 
      printf("%d, %f, %f, %f, %f, %f, %f \n",col, test[0],test[1],test[2], test[3], test[4], test[5]);
    }
  }



  delete input;
}
