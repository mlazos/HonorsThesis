function [im, classLabels, segim, tileLabels, true_pos, total_pos, false_pos, total_neg] = classifySingleImage(imseg, SVMStruct, vertClassifier, horzClassifier, segDensity, tileSize, beta)
 [im, segim] = processImageData(imseg, tileSize);
 [truthTiles, ~] = partition(segim,tileSize);
 tileLabels = squeeze(sum(sum(truthTiles))/(tileSize.^2) > .9); 
 [~, ~, ~, ~, featureVecs] = APPtestImage(im,[],vertClassifier,horzClassifier,segDensity, tileSize);
 s = size(featureVecs);
 classLabels = svmpredict(zeros(s(1),1),featureVecs(:,logical(beta)), SVMStruct, '-q');
 true_pos = sum(classLabels & tileLabels);
 total_pos = sum(tileLabels);
 false_pos = sum(classLabels & ~tileLabels);
 total_neg = sum(~tileLabels);
end

