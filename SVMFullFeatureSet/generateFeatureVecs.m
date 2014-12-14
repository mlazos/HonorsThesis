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
'calculating features...'
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
'calculating features... done!'