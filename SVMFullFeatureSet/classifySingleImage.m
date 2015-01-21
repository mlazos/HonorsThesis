function [classLabels, true_pos, total_pos, false_pos, total_neg] = classifySingleImage(imseg, SVMStruct, beta)
 tileLabels = imseg.feature_labels;
 s = size(imseg.features(:,logical(beta)));
 classLabels = svmpredict(zeros(s(1),1),imseg.features(:,logical(beta)), SVMStruct, '-q');
 true_pos = sum(classLabels & tileLabels);
 total_pos = sum(tileLabels);
 false_pos = sum(classLabels & ~tileLabels);
 total_neg = sum(~tileLabels);
end

