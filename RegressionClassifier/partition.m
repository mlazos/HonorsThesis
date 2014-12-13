function [partitions, colRowPos] = partition( mat, tileSize )
%Takes an image and partitions it into pieces of tileSize x tileSize
%If m is not evenly divisible in both dimensions, it will output only the
%tiles which are tileSize x tileSize
%Input:
%   mat -  matrix
%   tileSize - the tileSize to use
%
%Output:
%   partitions - the array of tiles
%   colRowPos - an colIters*rowIters X 2 array that contains the xy
%   position of each tile.

imSize = size(mat);
colIters = floor(imSize(2)/tileSize);
rowIters = floor(imSize(1)/tileSize);
partitions = zeros(tileSize,tileSize,(rowIters + colIters - 2));

colRowPos = zeros(colIters*rowIters, 2);
numIters = 1;
for j = 1:rowIters
    for i = 1:colIters
        ylow = (j-1)*tileSize + 1;
        yhigh = j*tileSize;
        xlow = (i-1)*tileSize + 1;
        xhigh = i*tileSize;
        partitions(:,:,numIters) = mat(ylow:yhigh,xlow:xhigh);
        colRowPos(numIters, :) = [i,j];
        numIters = numIters + 1;
    end
end



end

