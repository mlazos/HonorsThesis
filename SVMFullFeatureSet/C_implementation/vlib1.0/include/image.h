/* a simple image class */

#ifndef IMAGE_H
#define IMAGE_H

#include <cstring>

namespace vlib {

template <class T>
class image {
 public:
  /* create an image */
  image(const int width, const int height, const int pad = 0, const bool init = true);

  /* delete an image */
  ~image();

  /* init an image */
  void init(const T &val);

  /* copy an image */
  image<T> *copy() const;
  
  /* get the width of an image */
  int width() const { return w; }
  
  /* get the height of an image */
  int height() const { return h; }

  /* get the padding of an image */
  int pad() const { return pad; }
    
  /* row pointers, padded interface */
  T **access;
  
 private:
  T *data;
  T **row_ptrs;
  int full_w, full_h;
  int w, h, p;
};

/* use imRef to access image data. */
#define imRef(im, x, y) (im->access[y][x])
  
/* use imPtr to get pointer to image data. */
#define imPtr(im, x, y) &(im->access[y][x])

template <class T> 
  image<T>::image(const int width, const int height, const int pad, const bool init) {
  w = width;
  h = height;
  p = pad;
  full_w = w+2*p;
  full_h = h+2*p;
  data = new T[full_w * full_h];  // allocate space for image data
  row_ptrs = new T*[full_h];      // allocate space for row pointers  
  // initialize row pointers
  for (int i = 0; i < full_h; i++)
    row_ptrs[i] = data + (i * full_w) + p;  
  access = row_ptrs + p;
  
  if (init)
    memset(data, 0, full_w * full_h * sizeof(T));
}

template <class T>
image<T>::~image() {
  delete [] data; 
  delete [] row_ptrs;
}

template <class T>
void image<T>::init(const T &val) {
  T *ptr = data;
  T *end = data + full_w*full_h;
  while (ptr < end)
    *ptr++ = val;
}


template <class T>
image<T> *image<T>::copy() const {
  image<T> *im = new image<T>(w, h, p, false);
  memcpy(im->data, data, full_w * full_h * sizeof(T));
  return im;
}

}

#endif
  
