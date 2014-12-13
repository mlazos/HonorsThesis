function coloredIm = visualizeClassification( image, classLabels, tileSize )
%tiles is an axbxc matrix where axb are tile dimensions
%col_dim is the number of tiles across the image is

%construct mask of correctly classified regions
sizes = size(image);
mask = zeros(sizes(1),sizes(2));
tile = 1;
for row = 1:tileSize:sizes(1)
    for col = 1:tileSize:sizes(2)
        mask(row:(row+(tileSize-1)),col:(col+(tileSize-1))) = ...
            ones(tileSize,tileSize) .* classLabels(tile)/5;
        tile = tile + 1;
    end
end
coloredIm = image;
mask = mask + (mask == 0);
coloredIm(:,:,1) = image(:,:,1).*mask;
coloredIm(:,:,3) = image(:,:,3).*mask;
end

