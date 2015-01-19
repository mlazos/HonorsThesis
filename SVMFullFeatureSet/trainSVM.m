'training...'
C = 3;%2.9,2.95,3,3.05,3.1];
numSVMs = length(C);
parfor i = 1:numSVMs
    LSVMrbf(i) = svmtrain(LABELS, FEATURES,sprintf('-s 0 -c %d -t 2 -g 1/82',C(i)));
end
'training... done!'






