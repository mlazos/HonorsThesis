#include "train_svm.h"


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
  int tile_size = TILE_DIM;


  int num_files;
  char** training_files = load_filenames(input_name, &num_files);
  char** truth_files = load_filenames(truth_name, &num_files); 

  //calculate total number of features to allocate memory
  image<rgb> *input = loadPPM(training_files[2]); 
  int height = input->height();
  int width = input->width();
  int num_tiles = (width/tile_size) * (height/tile_size);
  int total_features = num_tiles * (num_files - 2)/2;
  matrix<float>* features = new matrix<float>(total_features, NUM_FEATURES, true);
  double *labels = new double[total_features];


  //compute features
  int features_computed = 0;
  for(int ind = 2; ind < num_files; ind += 2) {
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
  param->kernel_type = POLY;
  param->C = 3;
  param->eps = 0.001;//0.0001;
  param->gamma = 1;
  param->degree = 5;
  param->shrinking = 0;
  param->probability = 0;
  param->nr_weight = 0;
  param->cache_size = 100;
  
  const char* err = svm_check_parameter(prob, param);
  if(err) {
    printf(err);
    exit(1);
  }
  printf("training on %d features\n", features_computed);

  for(int ind = 0; ind < 10; ind++) {
	svm_node* arr = prob->x[ind];
    int inc = 0;
    int i = arr[0].index;
    while(i != -1) {
      printf("%f ",arr[inc].value );
      inc++;
	  i = arr[inc].index;
    }
	printf("L: %f", prob->y[ind]);
    printf("\n");
  }

 

  svm_model *model = svm_train(prob, param);   

  svm_save_model("svm.model",model);
  

  delete input;
}


