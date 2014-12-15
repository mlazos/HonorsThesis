% 'training...'
% C = [2.9,2.95,3,3.05,3.1];
% numSVMs = length(C);
% FEATURES = features(1:numFeatureVecs,:);
% LABELS = truthLabels(1:numFeatureVecs);
% BETA = ones(82,1);
% parfor i = 1:numSVMs
%     LSVMrbf(i) = svmtrain(LABELS, FEATURES,sprintf('-s 0 -c %d -t 2 -g 1/82',C(i)));
% end
% 'training... done!'

'evaluating...'
evaluateSVM;
'evaluating... done!'

save EVALUATINGCS

linSVM = fitcsvm(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs),'Standardize',true);

'training...'
C = [2.9,2.95,3,3.05,3.1];
numSVMs = length(C);
BETA = linSVM.Beta;
FEATURES = features(1:numFeatureVecs,abs(linSVM.Beta) > .1);
LABELS = truthLabels(1:numFeatureVecs);

parfor i = 1:numSVMs
    LSVMrbf(i) = svmtrain(LABELS, FEATURES,sprintf('-s 0 -c %d -t 2 -g 1/82',C(i)));
end
'training... done!'

'evaluating...'
evaluateSVM;
'evaluating... done!'

save EVALUATINGREDUCEDFEATURESET





% SVMStruct = fitcsvm(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs),'KernelFunction','polynomial','Standardize',true);
% '1...'
% SVMStructRBF = fitcsvm(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs),'KernelFunction','rbf','Standardize',true);
% 
% '5...'
% libSVMStructrbf = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c .5 -t 2 -g 1/82 ');
% '6...'
% libSVMStructrbf1 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 1 -t 2 -g 1/82 ');
% '7...' 
% libSVMStructrbf2 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 5 -t 2 -g 1/82 ');
% '8...'
% libSVMStructrbf3 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 10 -t 2 -g 1/82 ');
% '9...'
% libSVMStructrbf4 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 7 -t 2 -g 1/82 ');
% 
% libSVMStructrbf6 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 5.5 -t 2 -g 1 ');
% 
% libSVMStructrbf7 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 5.3 -t 2 -g 1/82 ');
% 
% libSVMStructrbf8 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 4.8 -t 2 -g 1/82 ');
% 
% libSVMStrcutrbf9 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 20 -t 2 -g 1/82 ');
% 
% libSVMStructrbf10 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 4.5 -t 2 -g 1/82 ');
% 
% libSVMStructrbf11 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 4.3 -t 2 -g 1/82 ');
% 
% libSVMStrcutrbf12 = svmtrain(truthLabels(1:numFeatureVecs),features(1:numFeatureVecs,:),'-s 0 -c 50 -t 2 -g 1/82 ');
