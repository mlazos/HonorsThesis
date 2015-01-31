#include "feature_extraction.h"
#include "filter.h"


using namespace vlib;
using namespace hsv;
using namespace features;


char** load_filenames(char* dir_name, int* num_filenames) {
  //load all image names from folder
  int num_files = 0;
  DIR *dir;
  struct dirent *ent;
  char** files = new char*[150];
  if ((dir = opendir (dir_name)) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      char* file = new char[50];
      file = strcpy(file, dir_name);
      files[num_files] = strcat(file,ent->d_name);
      num_files++;
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
  }

  *num_filenames = num_files;
  return files;
}


int compute_labels(image<uchar> *truth, int tile_size, int init_row, double *labels) {
  int width = truth->width();
  int height = truth->height();

  int num_labels = init_row;
  for(int row = 0; row + tile_size < height; row += tile_size) {
    for(int col = 0; col + tile_size < width; col += tile_size) {
	  compute_label(truth, col, col + tile_size, row, row + tile_size, &(labels[num_labels]));  
	  num_labels++;
    }
  }
  
  return num_labels;

}



int compute_label(image<uchar> *truth, int col_start, int col_end, int row_start, int row_end, double *label) {
  int sum = 0;
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      sum = sum + (1 - imRef(truth, col, row));
	  }
  }
  int total = (row_end - row_start) * (col_end - col_start);
  if((float)(sum/total) > .9) {
    *label = 1.0;
  }
  else {
  	*label = 0.0;
  }
  return 0;
}


/*
  compute features
  fills in features starting at init_row
  returns number of feature vectors (rows) added
*/
int compute_features(image<rgb> *input, int tile_size, int init_row,  matrix<float>* features) {
  image<hsv_float> *hsv_im = rgb_to_hsv_im(input);
  image<uchar> *gray = imageRGBtoGRAY(input);
  image<float> *smoothed = smooth(gray, 1.0);
  image<uchar> *edgeim = canny(smoothed, 1.0);
  
  int width = hsv_im->width();
  int height = hsv_im->height();

  
  int num_features = init_row;
  
  //calculate features over all tiles
  for(int row = 0; row + tile_size < height; row += tile_size) {
    for(int col = 0; col + tile_size < width; col += tile_size) {
      hsv_means(hsv_im, col, col + tile_size, row, row + tile_size, matPtr(features, num_features, 0));
      hue_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, 5, matPtr(features, num_features, 3)); 
      sat_histogram_features(hsv_im, col, col + tile_size, row, row + tile_size, 0, 1, 3, matPtr(features, num_features, 9)); 
      location_features(row, row + tile_size, input->height(), matPtr(features, num_features, 13));
      edge_centers(edgeim, col, col + tile_size, row, row + tile_size, matPtr(features,num_features, 14));          
      /* 
	    for(int i = 0; i < 3; i++) {
        printf("%f ", matRef(features, num_features, i));
      }
      printf("\n"); */
                    
      num_features++;
    }
  }
  delete hsv_im;
  delete smoothed;
  delete gray; 
  delete edgeim;

  return num_features; 

}

void print_features(matrix<float> *features, int start_feature, int end_feature, int num_features, double *labels) {

for(int row = 0; row < num_features; row++) {
  for(int col = start_feature; col < end_feature; col++) {
    printf("%f ", matRef(features, row, col));
  } 
  printf("L:%f", labels[row]);
  printf("\n");
}

}



svm_problem *convert_features(matrix<float> *features, double *labels) {
  int width = features->cols();
  int height = features->rows();
  svm_problem *prob = new svm_problem; 
  svm_node **nodes = new svm_node*[features->rows()];

  for(int row = 0; row < height; row++) {

    //count number of non-zero elements for allocation
    int num_els = 0;
    for(int col = 0; col < width; col++) {
      if(matRef(features, row, col) != 0) {
        num_els++;
      }
    }
    //create sparse representation
    svm_node *vec = new svm_node[num_els + 1];
    num_els = 0;
    for(int col = 0; col < width; col++) {
      if(matRef(features, row, col) != 0) {
        vec[num_els].value = matRef(features, row, col);
        vec[num_els].index = col + 1;
        num_els++;
      }
    }
    vec[num_els].index = -1;   
    nodes[row] = vec;
  }

  prob->x = nodes;
  prob->y = labels;
  prob->l = height;

  return prob;
}




