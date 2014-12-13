load('allimsegs2.mat');


%create classifiers struct
load('../GeometricContext/data/ijcvClassifier.mat');
load('../GeometricContext/data/ijcvClassifier_indoor.mat');
load('../GeometricContext/data/classifiers_08_22_2005.mat');
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

features = zeros(100000,82);
truthLabels = zeros(100000,1);
numFeatureVecs = 0;

training_set = dir('training_set/*.jpg');
sizes = size(training_set);
training_inds = zeros(sizes(1),1);
for i = 1:sizes(1)
    training_inds(i) = findimseg(training_set(i).name, imsegs);
end
'calulating features...'
for i = 1:length(training_inds)
    [im,segim] = processImageData(imsegs(training_inds(i)),tileSize);
    s = size(im);
    [~, ~, maps, ~, featureVecs] = APPtestImage(im,[],classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize);
    sizes = size(featureVecs);
    features((numFeatureVecs+1):(numFeatureVecs+sizes(1)),:) = featureVecs;
    [truthTiles, xydim] = partition(segim,tileSize);
    tileLabels = sum(sum(truthTiles))/(tileSize^2) > .9;
    truthLabels((numFeatureVecs+1):(numFeatureVecs+sizes(1)),:) = tileLabels;
    numFeatureVecs = numFeatureVecs + sizes(1);
end
'training...'
SVMStruct = fitcsvm(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs),'KernelFunction','polynomial','Standardize',true);
'1...'
SVMStructRBF = fitcsvm(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs),'KernelFunction','rbf','Standardize',true);

'5...'
libSVMStructrbf = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c .5 -t 2 -g 1/82 ');
'6...'
libSVMStructrbf1 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 1 -t 2 -g 1/82 ');
'7...' 
libSVMStructrbf2 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 5 -t 2 -g 1/82 ');
'8...'
libSVMStructrbf3 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 10 -t 2 -g 1/82 ');
'9...'
libSVMStructrbf4 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 7 -t 2 -g 1/82 ');

libSVMStructrbf6 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 5.5 -t 2 -g 1 ');

libSVMStructrbf7 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 5.3 -t 2 -g 1/82 ');

libSVMStructrbf8 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 4.8 -t 2 -g 1/82 ');

libSVMStrcutrbf9 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 20 -t 2 -g 1/82 ');

libSVMStructrbf10 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 4.5 -t 2 -g 1/82 ');

libSVMStructrbf11 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 4.3 -t 2 -g 1/82 ');

libSVMStrcutrbf12 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 50 -t 2 -g 1/82 ');
