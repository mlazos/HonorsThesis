%Generate transition probability matrix for markov model

%
NUM_STATES = 20;
NUM_NODES = 27;
VARIANCE = 2.0;


transition = zeros(NUM_STATES,NUM_STATES);


%1.16,1.35,4.25 -> .9444
%1.16, 1.40,4.25 -> 
%1.07, 1.20,4.25 -> .9437
%.9,1.40,4.50 -> .9435
%.9,1.40,4.75 -> .94126
%.9,1.40,4.0 -> .9461
%1.16,1.35,4.0 -> .9418
%.9,1.40,3.75 ->.9444
%1,1.40,3.85 -> .9439
%.9,1.40,4.15 ->  .946633
%.9,1.40,4.20 -> .9459
%.9,1.40,4.07 -> .9461
%.9,1.40,4.11 -> .9462
%.0,1.40,


for i = 1:20
    G = fspecial('Gaussian', [2*NUM_STATES - 1,1], .9 +(1.40/19)*(i-1)*1.40);
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