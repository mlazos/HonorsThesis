test_set = dir('../bandhdataset/*.jpg');
imnum = 1;
image_data = repmat(struct('name','n','image',zeros(2000,2000),'ground_truth',zeros(2000,2000)),[101,1]);
lowpass = fspecial('gaussian', [5,5], 1);
for i = 1:101
    figure;
    im = imread(['../bandhdataset/',test_set(i).name]);
    im = imfilter(im,lowpass);
    im = im(1:4:end,1:4:end,:);
    mask = roipoly(im);
    imnum = imnum + 1;
    image_data(imnum).name = test_set(i).name;
    image_data(imnum).image = im;
    image_data(imnum).ground_truth = mask;
end