tileSize = 30;
for i = test_inds(50:59)
    imseg = image_data(i);
    [im, labels, segim, truth, numCorrect, total] = classifySingleImage(imseg, LSVMrbf, classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize, BETA);
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

clear imseg learned correct im labels segim truth numCorrect total i

