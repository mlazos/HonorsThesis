'training...'
C = 3;%2.9,2.95,3,3.05,3.1];

parfor i = 1:size(BETA, 1)
    LSVMrbf(i) = svmtrain(LABELS, FEATURES(:,logical(BETA(i,:))),sprintf('-s 0 -c %d -t 2 -g 1/82',C));
end
clear numSVMs C
'training... done!'





