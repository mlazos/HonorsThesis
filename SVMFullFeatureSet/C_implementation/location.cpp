#include "location.h"


namespace features {

int location_features(int row_start, int row_end, float* center) {
  
  *center = (row_start + row_end)/2;

  return 0;
}



}
