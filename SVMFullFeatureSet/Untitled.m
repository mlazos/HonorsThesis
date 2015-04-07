% for i = 120:length(new_image_data)
%     [~,name,~] = fileparts(new_image_data(i).name);
%     imwrite(new_image_data(i).ground_truth, ['./pbm/',name, '.pbm']);
% end
ext_files = dir('outims/*.ppm');
ext_len = length(ext_files);
for i = 1:ext_len
    [~,name,~] = fileparts(ext_files(i).name);
    imwrite(imread(ext_files(i).name),['./sample_images/',name,'.jpg']);
end

% imSize = size(X);
% colIters = floor(imSize(2)/tileSize);
% rowIters = floor(imSize(1)/tileSize);
% 
% %partitions = zeros(tileSize,tileSize,(rowIters + colIters - 2));
% 
% %colRowPos = zeros(colIters*rowIters, 2);
% 
% segimage = rgb2gray(X);
% varimage = ones(rowIters, colIters);
% 
% for row = 1:rowIters
%     for col = 1:colIters
%         ylow = (row-1)*tileSize + 1;
%         yhigh = row*tileSize;
%         xlow = (col-1)*tileSize + 1;
%         xhigh = col*tileSize;
%         tile = segimage(ylow:yhigh, xlow:xhigh);
%         varimage(row, col) = var(tile(:));
%     end
% end