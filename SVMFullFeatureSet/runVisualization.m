for i = test_inds(10:20)
    imseg = image_data(i);
    [im, labels, segim, truth, numCorrect, total] = classifySingleImage(imseg, SVMStruct, classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize, ones(1,82));
    learned = visualizeClassification(im,labels,tileSize);
    correct = visualizeClassification(im,truth, tileSize);
    figure;
    subplot(1,2,1);
    imagesc(learned);
    title([imseg.name, ' learned']);
    subplot(1,2,2);
    imagesc(correct);
    title([imseg.name, ' truth']);
end

