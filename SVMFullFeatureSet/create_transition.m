%Generate transition probability matrix for markov model

%
NUM_STATES = 20;
NUM_NODES = 27;
VARIANCE = 2.0;


transition = zeros(NUM_STATES,NUM_STATES);


%1.16,1.35 -> .9444
%1.16, 1.40 ->
%1.07, 1.20 -> .9437

for i = 1:20
    G = fspecial('Gaussian', [2*NUM_STATES - 1,1], .9 +(1.10/19)*(i-1)*1.10);
    X = G((21 - i):(40 - i));
    transition(:,i) = X./sum(X);
end

transition

fid = fopen('transition_matrix.txt','wt+');
for i = 1:20
  for j = 1:20
    fprintf(fid,'%2.20f\n',transition(i,j));
  end
end
fclose(fid);