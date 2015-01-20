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
sens = zeros(1,length(LSVMrbf));
fpr = zeros(1,length(LSVMrbf));
acc = zeros(1,length(LSVMrbf));
j = 1;





for SVM = LSVMrbf

start = cputime;
true_pos = zeros(1,length(test_inds));
total_pos = zeros(1,length(test_inds));
false_pos = zeros(1,length(test_inds));
total_neg = zeros(1,length(test_inds));

parfor i = 1:length(test_inds)
    [~, ~, ~, ~, true_pos(i), total_pos(i), false_pos(i), total_neg(i)] = classifySingleImage(image_data(test_inds(i)), SVM, classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize, BETA);
end


sens(j) = sum(true_pos)/sum(total_pos);
fpr(j) = sum(false_pos)/sum(total_neg);
acc(j) = (sum(true_pos) + (sum(total_neg) - sum(false_pos)))/(sum(total_pos) + sum(total_neg));

j = j + 1;
end

clearvars -except FEATURES NOLOCS LABELS BETA LSVMrbf classifiers training_inds test_inds image_data numFeatureVecs sens fpr acc segment_density

sens
fpr
acc
