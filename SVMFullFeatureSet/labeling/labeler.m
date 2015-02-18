ext_files = dir('ext/*.jpg');
load bandhdata
curr_data_len = length(image_data);
ext_len = length(ext_files);
imnum = length(image_data);
new_image_data = repmat(struct('name','n','image',zeros(2000,2000),'ground_truth',zeros(2000,2000),'features', zeros(1,82),...
    'feature_labels', zeros(1,1),'tile_size',0), [ext_len + curr_data_len,1]);
new_image_data(1:curr_data_len) = image_data;
lowpass = fspecial('gaussian', [5,5], 1);
for i = 1:ext_len
    figure;
    im = imread(['ext/',ext_files(i).name]);
    im = imfilter(im,lowpass);
    im = im(1:4:end,1:4:end,:);
    mask = roipoly(im);
    imnum = imnum + 1;
    new_image_data(imnum).name = ext_files(i).name;
    new_image_data(imnum).image = im;
    new_image_data(imnum).ground_truth = mask;
end

clear lowpass imnum ext_len curr_data_len mask im test_set