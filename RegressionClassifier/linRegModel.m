load('allimsegs2.mat');


features = zeros(100000,11);
truthLabels = zeros(100000,1);
numFeatureVecs = 0;
for i = 1:5
    im = imread(['../cmuGeometricContextDataset/', imsegs(i).imname]);
    featureVecs = calcFeatures(im, 10);
    sizes = size(featureVecs);
    features((numFeatureVecs+1):(numFeatureVecs+sizes(1)),:) = featureVecs;
    segim = imsegs(i).segimage;
    labels = transpose(imsegs(i).labels);
    segim = subsValues(segim,1:length(labels),labels);
    segim = segim == 1;
    [truthTiles, xydim] = partition(segim,10);
    tileLabels = mean(mean(truthTiles)) > .5; %if mean > .5 => ground
    truthLabels((numFeatureVecs+1):(numFeatureVecs+sizes(1)),:) = squeeze(tileLabels);
    numFeatureVecs = numFeatureVecs + sizes(1);
end
%w = determineWeights(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs));
SVMStruct = svmtrain(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs), 'boxconstraint',.5, 'tolkkt', 1e-2, 'kktviolationlevel',.1);


