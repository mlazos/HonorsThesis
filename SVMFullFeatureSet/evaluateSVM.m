
load('allimsegs2.mat');
test_set = dir('test_set/*.jpg');
sizes = size(test_set);
test_inds = zeros(sizes(1),1);
for i = 1:sizes(1)
    test_inds(i) = findimseg(test_set(i).name, imsegs);
end

tileSizes = 30;
sens = zeros(1,length(tileSizes));
fpr = zeros(1,length(tileSizes));
acc = zeros(1,length(tileSizes));
j = 1;
dims = zeros(length(tileSizes),20);

for SVM = LSVMrbf

start = cputime;
true_pos = zeros(1,length(test_inds));
total_pos = zeros(1,length(test_inds));
false_pos = zeros(1,length(test_inds));
total_neg = zeros(1,length(test_inds));

parfor i = 1:length(test_inds)
    [~, ~, ~, ~, true_pos(i), total_pos(i), false_pos(i), total_neg(i)] = classifySingleImage(imsegs(test_inds(i)), SVM, classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize, linSVM.Beta);
end


sens(j) = sum(true_pos)/sum(total_pos);
fpr(j) = sum(false_pos)/sum(total_neg);
acc(j) = (sum(true_pos) + (sum(total_neg) - sum(false_pos)))/(sum(total_pos) + sum(total_neg));

j = j + 1;
end
%if low order polynomial is doing better than radial basis functions, 
%should regularize more
%show it on an image, and try to determine what features are more relevant.

sens
fpr
acc
