%load images
im = imread('../test_dir/images/alley01.jpg');
im = im2double(im);
%create classifiers struct
load('../data/ijcvClassifier.mat');
load('../data/ijcvClassifier_indoor.mat');
load('../data/classifiers_08_22_2005.mat');
classifiers.ecal = ecal;
classifiers.eclassifier = eclassifier;
classifiers.hclassifier = hclassifier;
classifiers.hclassifierSP = hclassifierSP;
classifiers.horz_classifier = horz_classifier;
classifiers.sclassifier = sclassifier;
classifiers.segment_density = segment_density;
classifiers.vclassifier = vclassifier;
classifiers.vclassifierSP = vclassifierSP;
classifiers.vert_classifier = vert_classifier;

tileSize = 10;
s = size(im);

im = im(1:(floor(s(1)/tileSize) * tileSize),1:(floor(s(2)/tileSize) * tileSize), :);
size(im);
[labels, conf_map, maps, pmaps, regionFeatures] = APPtestImage(im,[],classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize);