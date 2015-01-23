#include <cstdio>
#include <cstdlib>
#include <climits>
#include "pnmfile.h"
#include "hsv_conversion.h"

using namespace vlib;

#define MAX(x,y) (x) > (y) ? (x) :  (y)
#define MIN(x,y) (x) < (y) ? (x) :  (y)


namespace hsv {
    image<hsv_float> *rgb_to_hsv_im(image<rgb> *input_im) { 
    
    int width = input_im->width();
    int height = input_im->height();

    image<hsv_float> *hsv_im = new image<hsv_float>(width, height);
    for(int row = 0; row < height; row++) {
      for(int col = 0; col < width; col++) {
        imRef(hsv_im, col, row) = rgb_to_hsv(imRef(input_im, col, row));
      }  
    }

    return hsv_im;
    
    }

    hsv_float rgb_to_hsv(const rgb value ){
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
