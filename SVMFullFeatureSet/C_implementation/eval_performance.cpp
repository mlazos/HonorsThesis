#include "classify_image.h"

using namespace vlib;
using namespace hsv;
using namespace features;

int main(int argc, char **argv) {
  if (argc != 6) {
    fprintf(stderr, "usage: %s input(ppm) output(ppm) sigma\n", argv[0]);
    return 1;
  }

  char *input_name = argv[1];
  char *ground_truth_name = argv[2];
  char *output_name = argv[3];
  int tile_size = atoi(argv[4]);
  double sigma = atof(argv[5]);
  


  //calculate total number of features to allocate memory
  image<rgb> *input = loadPPM(input_name); 

  int height = input->height();
  int width = input->width();
  int num_tiles = (width/tile_size) * (height/tile_size);
  int total_features = num_tiles;
  matrix<float>* features = new matrix<float>(total_features, 16, true);
  double *labels = new double[total_features];
  double *test_labels = new double[total_features];

  //compute features
  int features_computed = 0;
  image<uchar> *truth = loadPBM(ground_truth_name); 
  compute_features(input, tile_size, features_computed, features);
  compute_labels(truth, tile_size, features_computed, labels);
  delete truth;
  
  
  svm_problem *prob = convert_features(features, labels);
  svm_model *model = svm_load_model("svm.model"); 

 
  for(int ind = 0; ind < total_features; ind++) {
    test_labels[ind] = svm_predict(model, prob->x[ind]);  
  }

  int acc_num = 0;
  int acc_denom = 0;
  int sens_num = 0;
  int sens_denom = 0;
  int fpr_num = 0;
  int fpr_denom = 0;
  for(int ind = 0; ind < total_features; ind++) {
  	acc_num = acc_num + ((test_labels[ind] == labels[ind]) ? 1 : 0);
    acc_denom++;
    sens_num = sens_num + ((test_labels[ind] == 1 && labels[ind] == 1) ? 1 : 0);
    sens_denom = sens_denom + labels[ind];
    fpr_num = fpr_num + ((test_labels[ind] == 1 && labels[ind] == 0) ? 1 : 0);
    fpr_denom = fpr_denom + !labels[ind];
  }


  printf("Accuracy: %f\n", ((float)acc_num)/((float)acc_denom));
  printf("Sensitivity: %f\n", ((float)sens_num/((float)sens_denom)));
  printf("FP Rate: %f\n", ((float)fpr_num/((float)fpr_denom)));

  create_highlighted_image(input, tile_size, test_labels);
  
  savePPM(input, "out.ppm");
  delete input;
}


void create_highlighted_image(image<rgb> *input, int tile_size, double *labels) {
  int width = input->width();
  int height = input->height();
  int ind = 0;
  for(int row = 0; row + tile_size < height; row += tile_size) {
    for(int col = 0; col + tile_size < width; col += tile_size) {
	  if(labels[ind] == 1.0) { 
		color_tile(input, col, col + tile_size, row, row + tile_size);
      }
 	  ind++;
    }
  }
}

void color_tile(image<rgb> *input, int start_col, int end_col, int start_row, int end_row) {
  for(int row = start_row; row < end_row; row++) {
    for(int col = start_col; col < end_col; col++) {
      rgb new_value = imRef(input, col, row);
      new_value.r = new_value.r/5;
      new_value.b = new_value.b/5;
      imRef(input, col, row) = new_value;
    }
  }
}

