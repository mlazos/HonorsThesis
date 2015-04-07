function imsegs = im2superpixels(im, tileSize)

% prefix = num2str(floor(rand(1)*10000000));
% fn1 = ['./tmpim' prefix '.ppm'];
% fn2 = ['./tmpimsp' prefix '.ppm'];
% segcmd = '../segment/segment 0.8 100 100';
% 
% imwrite(im, fn1);
% system([segcmd ' ' fn1 ' ' fn2]);
% imsegs = processSuperpixelImage(fn2);
% 
% delete(fn1);
% delete(fn2);
imSize = size(im);
colIters = floor(imSize(2)/tileSize);
rowIters = floor(imSize(1)/tileSize);

%partitions = zeros(tileSize,tileSize,(rowIters + colIters - 2));

%colRowPos = zeros(colIters*rowIters, 2);

segimage = ones(rowIters*tileSize, colIters*tileSize);
adjmat = zeros(colIters*rowIters, colIters*rowIters);
numIters = 1;
for row = 1:rowIters
    for col = 1:colIters
        ylow = (row-1)*tileSize + 1;
        yhigh = row*tileSize;
        xlow = (col-1)*tileSize + 1;
        xhigh = col*tileSize;
        segimage(ylow:yhigh, xlow:xhigh) = numIters;
        adjmat = filladjmat(row,col,rowIters,colIters,adjmat);        
        numIters = numIters + 1;
    end
end

npixels = ones(colIters * rowIters,1) * tileSize * tileSize;

nseg = colIters * rowIters;

imname = 'temp.ppm';
imsize = [rowIters*10, colIters*10];
 
 
imsegs = struct('imname', imname, 'imsize', imsize, 'segimage', segimage, 'nseg', nseg, 'npixels', npixels, 'adjmat', adjmat);


