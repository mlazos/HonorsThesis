function p = accuracy(imsegs, SVMStruct)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
 im = imread(['../cmuGeometricContextDataset/', imsegs.imname]);
 segim = imsegs.segimage;
 labels = transpose(imsegs.labels);
 segim = subsValues(segim,1:length(labels),labels);
 segim = segim == 1;
 [truthTiles, ~] = partition(segim,10);
 tileLabels = squeeze(mean(mean(truthTiles)) > .5); %if mean > .5 => ground
 featureVecs = calcFeatures(im, 10);
 classLabels = svmclassify(SVMStruct, featureVecs);%featureVecs * w > .5;
 p = mean(tileLabels == classLabels);
end

