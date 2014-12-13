%tileSize = 40;
%trainSVM;
for i = training_inds(1:20)'
    imseg = imsegs(i);
    [im, labels, segim, truth, numCorrect, total] = classifySingleImage(imseg, SVMStruct, classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize, linSVM.Beta);
    learned = visualizeClassification(im,labels,tileSize);
    correct = visualizeClassification(im,truth, tileSize);
    figure;
    subplot(1,2,1);
    imagesc(learned);
    title([imseg.imname, ' learned']);
    subplot(1,2,2);
    imagesc(correct);
    title([imseg.imname, ' truth']);
end

