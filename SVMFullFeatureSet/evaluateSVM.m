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
sens = zeros(size(BETA,1), 1);
fpr = zeros(size(BETA,1), 1);
acc = zeros(size(BETA,1), 1);
j = 1;





for b = 1:size(BETA,1)

start = cputime;
true_pos = zeros(1,length(test_inds));
total_pos = zeros(1,length(test_inds));
false_pos = zeros(1,length(test_inds));
total_neg = zeros(1,length(test_inds));

B = BETA(b,:);
SVM = LSVMrbf(b);
parfor i = 1:length(test_inds)
    [~, true_pos(i), total_pos(i), false_pos(i), total_neg(i)] = classifySingleImage(image_data(test_inds(i)), SVM, B);
end


sens(b) = sum(true_pos)/sum(total_pos);
fpr(b) = sum(false_pos)/sum(total_neg);
acc(b) = (sum(true_pos) + (sum(total_neg) - sum(false_pos)))/(sum(total_pos) + sum(total_neg));
end

clearvars -except FEATURES NOLOCS LABELS BETA LSVMrbf classifiers training_inds test_inds image_data numFeatureVecs sens fpr acc segment_density

sens
fpr
acc
