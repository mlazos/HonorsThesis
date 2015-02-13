#include "location.h"


namespace features {

int location_features(int row_start, int row_end, int height, float* center) {
  
  *center = (((float)row_start/height + (float)row_end/height)/2)/100;

  return 0;
}



}
