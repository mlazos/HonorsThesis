function labelProb = linreg( featureVecs, weights )
%This regression does a simple binary classification
labelProb = featureVecs * weights;
end

