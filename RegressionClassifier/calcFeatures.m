function [ featureVecs ] = calcFeatures( img, tileSize )
%This function takes an image and calculates the features of 
%tileSize X tileSize sections of the image

[Rtiles, xypos] = partition(img(:,:,1), tileSize);
[Gtiles, ~] = partition(img(:,:,2), tileSize);
[Btiles, ~] = partition(img(:,:,3), tileSize);
Rmean = squeeze(mean(mean(Rtiles)));
Gmean = squeeze(mean(mean(Gtiles)));
Bmean = squeeze(mean(mean(Btiles)));
s = size(Rmean);
featureVecs = [ones(s(1),1),xypos,xypos.^2,Rmean,Gmean,Bmean,Rmean.^2,Gmean.^2,Bmean.^2];



end

