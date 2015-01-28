#include "classify_image.h"


using namespace vlib;
using namespace hsv;
using namespace features;

int main(int argc, char **argv) {
  /*if (argc != 5) {
    fprintf(stderr, "usage: %s input(ppm) output(ppm) sigma\n", argv[0]);
    return 1;
  }

  char *input_name = argv[1];
  char *output_name = argv[2];
  int tile_size = atoi(argv[3]);
  double sigma = atof(argv[4]);
  */
  char *input_name = "./ppm_images/";
  char *truth_name = "./ground_truth/";
  int tile_size = 30;


  int num_files;
  char** training_files = load_filenames(input_name, &num_files);
  char** truth_files = load_filenames(truth_name, &num_files); 

  //calculate total number of features to allocate memory
  image<rgb> *input = loadPPM(training_files[2]); 
  int height = input->height();
  int width = input->width();
  int num_tiles = (width/tile_size) * (height/tile_size);
  int total_features = num_tiles * (num_files - 2);
  matrix<float>* features = new matrix<float>(total_features, 16, true);
  double *labels = new double[total_features];


  //compute features
  int features_computed = 0;
  for(int ind = 2; ind < num_files; ind++) {
    image<rgb> *input = loadPPM(training_files[ind]);
    image<uchar> *truth = loadPBM(truth_files[ind]); 
    compute_features(input, tile_size, features_computed, features);
  	features_computed = compute_labels(truth, tile_size, features_computed, labels);
	  delete input;
    delete truth;
  }

  
  svm_problem *prob = convert_features(features, labels);
  svm_parameter *param = new svm_parameter;
  
  param->svm_type = C_SVC;
  param->kernel_type = RBF;
  param->C = 3;
  param->eps = 0.001;//0.0001;
  param->gamma = 1/82;
  param->degree = 1;
  param->shrinking = 0;
  param->probability = 0;
  param->nr_weight = 0;
  param->cache_size = 100;
  
  const char* err = svm_check_parameter(prob, param);
  if(err) {
    printf(err);
    exit(1);
  }


  svm_model *model = svm_train(prob, param);   

  delete input;
}

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
      num_labels++;;
    }
  }

  return num_labels;

}



int compute_label(image<uchar> *truth, int col_start, int col_end, int row_start, int row_end, double *label) {
  int sum = 0;
  for(int row = row_start; row < row_end; row++) {
    for(int col = col_start; col < col_end; col++) {
      sum = sum + imRef(truth, col, row);
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
      for(int ind = 0; ind < 16; ind++) {
        printf("%f ", matRef(features, num_features, ind));
      } 
      printf("\n");
	  */
      num_features++;
    }
  }
  delete hsv_im;
  delete smoothed;
  delete gray; 
  delete edgeim;

  return num_features; 

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
      if(matRef(features, row, col) != 0.0) {
        num_els++;
      }
    }
    //create sparse representation
    svm_node *vec = new svm_node[num_els + 1];
    num_els = 0;
    for(int col = 0; col < width; col++) {
      if(matRef(features, row, col) != 0.0) {
        vec[num_els].value = matRef(features, row, col);
        vec[num_els].index = col;
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





