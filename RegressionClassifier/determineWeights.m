function w = determineWeights( featureVecs, labels)
%determines the weights for a linear regression model given a training set
%of feature vectors and labels
X = featureVecs;
Xt = transpose(featureVecs);

w = (Xt*X)\Xt*labels;

end

