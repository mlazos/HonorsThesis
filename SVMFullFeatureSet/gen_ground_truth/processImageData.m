function [ image, groundTruth ] = processImageData( imseg, tileSize )
%PROCESSIMAGEDATA 
%takes an input image, and the ground truth segment, and generates the
%binary ground truth and image
 im = imread((['../cmuGeometricContextDataset/', imseg.imname]));
 s = size(im);
 image = im2double(im(1:(floor(s(1)/tileSize) * tileSize),1:(floor(s(2)/tileSize) * tileSize), :));
 segim = imseg.segimage;
 labels = transpose(imseg.labels);
 segim = subsValues(segim,1:length(labels),labels);
 groundTruth = segim == 1;
end

