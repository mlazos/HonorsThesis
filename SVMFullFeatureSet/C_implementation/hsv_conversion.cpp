#include <cstdio>
#include <cstdlib>
#include <climits>
#include "pnmfile.h"
#include "filter.h"

using namespace vlib;

#define MAX(x,y) (x) > (y) ? (x) :  (y)
#define MIN(x,y) (x) < (y) ? (x) :  (y)


namespace hsv {

    hsv_float rgbToHsv(const rgb value ){
      double r = value.r/255;
      double g = value.g/255;
      double b = value.b/255;
      double max = MAX(MAX(r,g),b);
      double min = MIN(MIN(r,g),b);
      double h, s, v;
      v = max;

      double d = max - min;
      s = max == 0 ? 0 : (d / max);

      if(max == min){
          h = 0; // achromatic
      }else{
          if(max ==  value.r) {
            h = (g - b) / d + (g < b ? 6 : 0);
          } else if(max == value.g) {
            h = (b - r) / d + 2;
          } else if(max == value.b) {
            h = (r - g) / d + 4;
          }
        h = h/6;
      }

      hsv_float ret_val;
      ret_val.h = h;
      ret_val.s = s;
      ret_val.v = v;   
      return ret_val;
    }   

}
