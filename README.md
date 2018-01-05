# Honors Thesis - Automatic Pixel Classification for Indoor Navigation

This is an implementation of a custom model for classifying navigable terrain for a small robot. The model consists of an SVM paired with an HMM for smoothing.

## Getting Started

1. Clone the repo
2. Navigate to HonorsThesis\SVMFullFeatureSet\C_implementation
3. Run make all

#### Training the SVM
1. Create a directory under C_implementation called ppm_images
2. Populate that directory with training images in PPM format
3. Create a second directory under C_implementation called ground_truth
4. Populate that directory with binary images in PBM format. Ensure that each binary image has the same name as its associated PPM file (except extension of course). Pixels with value 1 are considered navigable.
5. Run ./train_svm from the C_implementation directory.

#### Classifying a whole dataset
1. Create a directory under C_implementation called test_data
2. Populate that directory with your test images in PPM format.
3. Create a second directory under C_implementation called test_truth
4. Populate that directory with binary images in PBM format. Ensure that each binary image has the same name as its associated PPM file (except extension). Pixels with value 1 are considered navigable.
5. Create a third directory called validation_data
6. Populate that directory with some validation images in PPM format.
7. Create a fourth directory called validation_truth
8. Populate that directory with binary images in PBM format. Ensure that each binary image has the same name as its associated PPM file in the validation_data directory (except extension). Pixels with value 1 are considered navigable.
9. Run ./classify_dataset, it will print some statistics on the performance of the classifier.

#### Classifying a single image
1. Run ./classify_image <input ppm> <ground truth pbm> <output ppm name> <tile size> <sigma>,  tile size is the size of the tiles that features are computed from in the image, sigma can be any value.

### Prerequisites

* A C++ compiler for your OS.
* Some labeled data. A nice MATLAB labeler is located under HonorsThesis\SVMFullFeatureSet\labeling, which worked pretty well for generating my data, but it might have to be tweaked for your use case.
