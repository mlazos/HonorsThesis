function regionLabels = spTruth2RegionTruth(sp2regionMap, spGroundTruth, nRegions )

regionLabels = zeros(nRegions,1);
for r = 1:nRegions
    labels4Region = spGroundTruth(sp2regionMap == r);
    regionLabels(r) = mean(labels4Region) > .5;
end

end

