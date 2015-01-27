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
  
  //find centers of edge mass for x,y
  float centerx = sumedgex/sumx;
  float centery = sumedgey/sumy;

  //printf("%f\n", centerx);
  //printf("%f\n", centery);

  sumedgex = 0;
  sumedgey = 0;

  //find center of mass of region within edge centers;
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      if(col/width < centerx) {
        sumedgex = sumedgex + col/width;
      }
      if(row/height < centery) {
        sumedgey = sumedgey + row/height;
      }
    }
  }

  //printf("%f\n", sumedgex);
  //printf("%f\n", sumedgey); 

  //edge center x
  edge_centers[0] = sumedgex/sumx;
  //edge center y
  edge_centers[1] = sumedgey/sumy;

  //printf("%f\n", edge_centers[0]);
 
  //printf("%f\n", edge_centers[1]);



  return 0;

}



}
