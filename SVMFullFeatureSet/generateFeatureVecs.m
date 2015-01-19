%load 'bandhdata.mat'

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

tileSize = 30;
features = zeros(100000,82);
truthLabels = zeros(100000,1);
numFeatureVecs = 0;

sizes = size(image_data);
training_inds = 1:2:sizes(1);

'calculating features...'
for i = 1:length(training_inds)
    [im,segim] = processImageData(image_data(i),tileSize);
    s = size(im);
    [~, ~, maps, ~, featureVecs] = APPtestImage(im,[],classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize);
    sizes = size(featureVecs);
    features((numFeatureVecs+1):(numFeatureVecs+sizes(1)),:) = featureVecs;
    [truthTiles, xydim] = partition(segim,tileSize);
    tileLabels = sum(sum(truthTiles))/(tileSize^2) > .9;
    truthLabels((numFeatureVecs+1):(numFeatureVecs+sizes(1)),:) = tileLabels;
    numFeatureVecs = numFeatureVecs + sizes(1);
end
FEATURES = features(1:numFeatureVecs,:);
LABELS = truthLabels(1:numFeatureVecs);
clearvars -except FEATURES LABELS training_inds image_data numFeatureVecs
BETA = ones(1,82);
'calculating features... done!'