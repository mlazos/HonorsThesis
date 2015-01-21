tileSize = 30;
for i = test_inds(1:59)
    imseg = image_data(i);
    [labels, ~, ~, ~, ~] = classifySingleImage(imseg, LSVMrbf,  BETA);
    [im, ~] = processImageData(imseg, tileSize);
    learned = visualizeClassification(im, labels, tileSize);
    correct = visualizeClassification(im, imseg.feature_labels, tileSize);
    figure;
    subplot(1,2,1);
    imagesc(learned);
    title([imseg.name, ' learned']);
    subplot(1,2,2);
    imagesc(correct);
    title([imseg.name, ' truth']);
end

clear imseg learned correct im labels segim truth numCorrect total i

