function [im, classLabels, segim, tileLabels, true_pos, total_pos, false_pos, total_neg] = classifySingleImage(imseg, SVMStruct, vertClassifier, horzClassifier, segDensity, tileSize, beta)
 [im, segim] = processImageData(imseg, tileSize);
 [truthTiles, ~] = partition(segim,tileSize);
 tileLabels = squeeze(sum(sum(truthTiles))/(tileSize.^2) > .9); 
 [~, ~, ~, ~, featureVecs] = APPtestImage(im,[],vertClassifier,horzClassifier,segDensity, tileSize);
 %classLabels = predict(SVMStruct, featureVecs);
  s = size(featureVecs);
  classLabels = svmpredict(zeros(s(1),1),featureVecs(:,abs(beta) > .1), SVMStruct, '-q');
%  sizes = size(classLabels);
%  shiftup = circshift(classLabels,[1,0]);
%  shiftdown = circshift(classLabels,[-1,0]);
%  lower = 2;
%  upper = (sizes(1) - 1);
%  classLabels(lower:upper) = shiftdown(lower:upper) & classLabels(lower:upper) | shiftup(lower:upper) & classLabels(lower:upper) | shiftup(lower:upper) & shiftdown(lower:upper);
 true_pos = sum(classLabels & tileLabels);
 total_pos = sum(tileLabels);%length(tileLabels);
 false_pos = sum(classLabels & ~tileLabels);
 total_neg = sum(~tileLabels);
end

