%Generate transition probability matrix for markov model

%
NUM_STATES = 20;
NUM_NODES = 27;
VARIANCE = 2;
G = fspecial('Gaussian', [2*NUM_STATES - 1,1],1);

transition = zeros(NUM_STATES,NUM_STATES);

for i = 1:20
    X = G((21 - i):(40 - i));
    transition(:,i) = X./sum(X);
end

transition