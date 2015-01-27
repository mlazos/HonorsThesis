#include "edge_centers.h"

using namespace vlib;

namespace features {

int edge_centers(image<uchar>* image, int col_start, int col_end, int row_start, int row_end, float* edge_centers) {
  
  float sumedgex = 0;
  float sumedgey = 0;
  float sumx = 0;
  float sumy = 0;
  int numP = 0;
  float width = (float)image->width();
  float height = (float)image->height();




  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      if(imRef(image, col, row) == 1) {
        sumedgex = sumedgex + col/width;
        sumedgey = sumedgey + row/height;
      }
      sumx = sumx + col/width;
      sumy = sumy + row/height;
      numP++;
    }
  }
  
  printf("%d %f %f\n", numP, sumx, sumy);
  //find centers of edge mass for x,y
  float centerx = sumedgex/sumx;
  float centery = sumedgey/sumy;

  printf("centers: %f %f", centerx, centery);

  sumedgex = 0;
  sumedgey = 0;

  //find center of mass of region within edge centers;
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      if(col < centerx) {
        sumedgex = sumedgex + col/width;
      }
      if(row < centery) {
        sumedgey = sumedgey + row/height;
      }
    }
  }

  //edge center x
  edge_centers[0] = sumedgex/sumx;
  //edge center y
  edge_centers[1] = sumedgey/sumy;


  return 0;

}



}
