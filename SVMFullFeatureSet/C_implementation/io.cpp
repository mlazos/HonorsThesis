#include "io.h"

using namespace vlib;

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

void print_features(matrix<float> *features, int start_feature, int end_feature, int num_features, double *labels) {
  for(int row = 0; row < num_features; row++) {
    for(int col = start_feature; col < end_feature; col++) {
      printf("%f ", matRef(features, row, col));
    } 
    printf("L:%f", labels[row]);
    printf("\n");
  }
}

