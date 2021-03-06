#include "train_svm.h"
#include "io.h"
#include "regularize.h"
#include "hmm.h"
#include "error_estimation.h"

using namespace vlib;
using namespace hsv;
using namespace features;
using namespace regularization;
using namespace models;


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





  char *input_name = "./test_data/";
  char *truth_name = "./test_truth/";
  int tile_size = TILE_DIM;

  int num_v_files;
  char *validation_dir = "./validation_data/";
  char *val_truth_dir = "./validation_truth/";
  char **v_files = load_filenames(validation_dir, &num_v_files);
  char **v_truth = load_filenames(val_truth_dir, &num_v_files);


  int num_files;
  char** training_files = load_filenames(input_name, &num_files);
  char** truth_files = load_filenames(truth_name, &num_files); 

  //calculate total number of features to allocate memory
  image<rgb> *input = loadPPM(training_files[2]); 
  int height = input->height();
  int width = input->width();
  int num_tiles = (width/tile_size) * (height/tile_size);
  matrix<float>* features = new matrix<float>(num_tiles, NUM_FEATURES, true);
  double *labels = new double[num_tiles];
  double *test_labels = new double[num_tiles];    
  

  //compute features

  int acc_num = 0;
  int acc_denom = 0;
  int sens_num = 0;
  int sens_denom = 0;
  int fpr_num = 0;
  int fpr_denom = 0;


  svm_model *model = svm_load_model("svm.model"); 
 

  //train validation histogram on validation data 
  for(int ind = 2; ind < num_v_files; ind += 1) {
	
    image<rgb> *input = loadPPM(v_files[ind]);
    image<uchar> *truth = loadPBM(v_truth[ind]); 
	compute_features(input, tile_size, 0, features);
    compute_labels(truth, tile_size, 0, labels);
    svm_problem *prob = convert_features(features, labels);
    for(int ind = 0; ind < num_tiles; ind++) {
      test_labels[ind] = svm_predict_s(model, prob->x[ind]);  
    }
	
	update_score_hist(num_tiles, test_labels, labels);

  }



  print_histogram();
 
  for(int ind = 2; ind < num_files; ind += 1) {
	
    image<rgb> *input = loadPPM(training_files[ind]);
    image<uchar> *truth = loadPBM(truth_files[ind]); 
	compute_features(input, tile_size, 0, features);
    compute_labels(truth, tile_size, 0, labels);
    svm_problem *prob = convert_features(features, labels);
    for(int ind = 0; ind < num_tiles; ind++) {
      test_labels[ind] = svm_predict_s(model, prob->x[ind]);  
    }

	regularize(test_labels,height/tile_size,width/tile_size);    


    for(int ind = 0; ind < num_tiles; ind++) {
  	  acc_num = acc_num + ((test_labels[ind] == labels[ind]) ? 1 : 0);
      acc_denom++;
      sens_num = sens_num + ((test_labels[ind] == 1 && labels[ind] == 1) ? 1 : 0);
      sens_denom = sens_denom + labels[ind];
      fpr_num = fpr_num + ((test_labels[ind] == 1 && labels[ind] == 0) ? 1 : 0);
      fpr_denom = fpr_denom + !labels[ind];
    }	

    create_highlighted_image(input, tile_size, test_labels);
    char *buf = new char[20];
    sprintf(buf,"./outims/out%d.ppm",ind);
    savePPM(input,buf);
    delete input;
    delete truth;
  }
 
 


  printf("Accuracy: %f\n", ((float)acc_num)/((float)acc_denom));
  printf("Sensitivity: %f\n", ((float)sens_num/((float)sens_denom)));
  printf("FP Rate: %f\n", ((float)fpr_num/((float)fpr_denom)));

  

}








