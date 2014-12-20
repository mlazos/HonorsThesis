load('multiSVMs2.mat')
trainSVM

ans =

calulating features...

Operation terminated by user during imfilter>filterPartOrWhole (line 369)


In imfilter (line 175)
  b = filterPartOrWhole(a, finalSize, h, pad, sameSize, convMode);

In edge>smoothGradient (line 528)
GX = imfilter(I, gaussKernel', 'conv', 'replicate');

In edge (line 209)
    [dx, dy] = smoothGradient(a, sigma);

In APPgetLargeConnectedEdges (line 23)
im_canny = edge(grayIm, 'canny');


In APPtestImage (line 45)
[vpdata.lines, vpdata.spinfo] = ...


In trainSVM (line 33)
    [~, ~, maps, ~, featureVecs] =
    APPtestImage(im,[],classifiers.vert_classifier,classifiers.horz_classifier,segment_density, tileSize);
 
generateFeatureVecs

ans =

calculating features...


ans =

calculating features... done!

trainSVM

ans =

training...

Undefined function or variable 'numFeatures'.

Error in trainSVM (line 4)
FEATURES = features(1:numFeatures,:);
 
trainSVM

ans =

training...

..............................................................................................................................*.................................................................*..*
optimization finished, #iter = 192534
nu = 0.004668
obj = -156670.431168, rho = -0.537676
nSV = 25332, nBSV = 56
Total nSV = 25332
............................................................................................................*............................................................*...*
optimization finished, #iter = 170777
nu = 0.007415
obj = -127902.200709, rho = -0.538937
nSV = 25416, nBSV = 102
Total nSV = 25416
............................................*...............*
optimization finished, #iter = 59990
nu = 0.116877
obj = -19316.712223, rho = -0.530024
nSV = 26534, nBSV = 2495
Total nSV = 26534
..........................................*................*
optimization finished, #iter = 58740
nu = 0.125910
obj = -18405.195427, rho = -0.529815
nSV = 26587, nBSV = 2661
Total nSV = 26587
...........................................*..............*.*
optimization finished, #iter = 57694
nu = 0.137165
obj = -17443.821853, rho = -0.529606
nSV = 26674, nBSV = 2841
Total nSV = 26674
........................................*...............*
optimization finished, #iter = 55283
nu = 0.151682
obj = -16421.537688, rho = -0.529482
nSV = 26766, nBSV = 3067
Total nSV = 26766
......................................*..............*.*
optimization finished, #iter = 52248
nu = 0.199049
obj = -14124.391707, rho = -0.530671
nSV = 27050, nBSV = 3829
Total nSV = 27050
...................................*...........*
optimization finished, #iter = 46937
nu = 0.264579
obj = -10585.728995, rho = -0.658981
nSV = 27747, nBSV = 9358
Total nSV = 27747

ans =

training... done!

evaluateSVM
Error using classifySingleImage (line 6)
Undefined function 'predict' for input arguments of type 'struct'.

Error in evaluateSVM (line 25)
parfor i = 1:length(test_inds)
 
evaluateSVM
Operation terminated by user during APPgetSpData (line 66)


In APPtestImage (line 39)
spdata = APPgetSpData(image, doog_filters, texton_data.tim, imsegs);


In classifySingleImage (line 5)
 [~, ~, ~, ~, featureVecs] = APPtestImage(im,[],vertClassifier,horzClassifier,segDensity, tileSize);

In parallel_function (line 478)
            consume(base, limit, F(base, limit, supply(base, limit)));

In evaluateSVM (line 25)
parfor i = 1:length(test_inds)
 
evaluateSVM

j =

     1


j =

     2


j =

     3


j =

     4


j =

     5


j =

     6


j =

     7


j =

     8


sens =

    0.5816    0.5979    0.5986    0.5977    0.5969    0.5957    0.5734    0.5728


fpr =

    0.0355    0.0407    0.0409    0.0409    0.0409    0.0409    0.0432    0.0441


acc =

    0.8522    0.8533    0.8533    0.8531    0.8529    0.8525    0.8444    0.8435

plot(C,sens)
plot(C(1:5),sens(1:5))
save checkingCforRBF
j

j =

     9

evaluateSVM

j =

     9


sens =

    0.5816    0.5979    0.5986    0.5977    0.5969    0.5957    0.5734    0.5728    0.5921


fpr =

    0.0355    0.0407    0.0409    0.0409    0.0409    0.0409    0.0432    0.0441    0.0410


acc =

    0.8522    0.8533    0.8533    0.8531    0.8529    0.8525    0.8444    0.8435    0.8514

sum(linSVM.Beta > .1)

ans =

    25

sum(linSVM.Beta > .01)

ans =

    29

sum(linSVM.Beta > 0)

ans =

    31

sum(abs(linSVM.Beta) > .1)

ans =

    54

sum(abs(linSVM.Beta) > .2)

ans =

    43

sum(abs(linSVM.Beta) > .1)

ans =

    54

fitcsvm(features(1:numFeatureVecs,:), truthLabels(1:numFeatureVecs),'Standardize',true);
Operation terminated by user during classreg.learning.impl.SVMImpl.make (line 415)


In ClassificationSVM (line 262)
            this.Impl = classreg.learning.impl.SVMImpl.make(...

In classreg.learning.FitTemplate/fit (line 243)
            obj = this.MakeFitObject(X,Y,W,this.ModelParams,fitArgs{:});

In ClassificationSVM.fit (line 235)
            this = fit(temp,X,Y);

In fitcsvm (line 279)
obj = ClassificationSVM.fit(X,Y,varargin{:});
 
size(linSVM.Beta)

ans =

    82     1

FEATURES = features(1:numFeatureVecs,abs(linSVM.Beta) > .1);
trainSVM;

ans =

training...

Error using subsasgn
You cannot set the read-only property 'Beta' of ClassificationSVM.

Error in classreg.learning.internal.DisallowVectorOps/subsasgn (line 33)
                [varargout{1:nargout}] = builtin('subsasgn',this,s,data);

Error in trainSVM (line 6)
linSVM.Beta = ones(82,1);
 
trainSVM

ans =

training...

........................................*...............*
optimization finished, #iter = 55774
nu = 0.148443
obj = -16631.470263, rho = -0.529494
nSV = 26750, nBSV = 3014
Total nSV = 26750
........................................*...............*
optimization finished, #iter = 55603
nu = 0.150040
obj = -16526.867380, rho = -0.529483
nSV = 26752, nBSV = 3040
Total nSV = 26752
........................................*...............*
optimization finished, #iter = 55283
nu = 0.151682
obj = -16421.537688, rho = -0.529482
nSV = 26766, nBSV = 3067
Total nSV = 26766
..........................................*.............*
optimization finished, #iter = 55525
nu = 0.153374
obj = -16315.461537, rho = -0.529473
nSV = 26777, nBSV = 3090
Total nSV = 26777
........................................*...............*
optimization finished, #iter = 55376
nu = 0.155118
obj = -16208.619019, rho = -0.529476
nSV = 26797, nBSV = 3109
Total nSV = 26797

ans =

training... done!


ans =

evaluating...

Undefined function or variable 'libSVMStructrbf2'.

Error in evaluateSVM (line 17)
for SVM = libSVMStructrbf2

Error in trainSVM (line 13)
evaluateSVM;
 
LSVMrbf

LSVMrbf = 

1x8 struct array with fields:

    Parameters
    nr_class
    totalSV
    rho
    Label
    sv_indices
    ProbA
    ProbB
    nSV
    sv_coef
    SVs

trainSVM

ans =

evaluating...


j =

     1


j =

     2


j =

     3


j =

     4


j =

     5


j =

     6


j =

     7


j =

     8


sens =

    0.5985    0.5985    0.5986    0.5989    0.5986    0.5957    0.5734    0.5728


fpr =

    0.0412    0.0411    0.0409    0.0410    0.0410    0.0409    0.0432    0.0441


acc =

    0.8532    0.8532    0.8533    0.8534    0.8533    0.8525    0.8444    0.8435


ans =

evaluating... done!


ans =

training...

................................*..............*
optimization finished, #iter = 46687
nu = 0.190316
obj = -25489.785140, rho = -0.461783
nSV = 17453, nBSV = 7374
Total nSV = 17453
................................*..............*.*
optimization finished, #iter = 46716
nu = 0.191340
obj = -25220.883654, rho = -0.461977
nSV = 17478, nBSV = 7429
Total nSV = 17478
................................*.............*
optimization finished, #iter = 45527
nu = 0.192378
obj = -24950.266848, rho = -0.462190
nSV = 17491, nBSV = 7470
Total nSV = 17491
...............................*.............*.*
optimization finished, #iter = 45051
nu = 0.193440
obj = -24677.900285, rho = -0.462414
nSV = 17519, nBSV = 7534
Total nSV = 17519
...............................*.............*..*
optimization finished, #iter = 45903
nu = 0.194526
obj = -24403.742222, rho = -0.462725
nSV = 17544, nBSV = 7592
Total nSV = 17544

ans =

training... done!


ans =

evaluating...


j =

     1


j =

     2


j =

     3


j =

     4


j =

     5


j =

     6


j =

     7


j =

     8


sens =

    0.7244    0.7249    0.7256    0.7260    0.7265         0         0         0


fpr =

    0.0825    0.0829    0.0830    0.0832    0.0834         0         0         0


acc =

    0.8609    0.8607    0.8609    0.8609    0.8609    0.7067    0.7067    0.7067


ans =

evaluating... done!

abs(linSVM.Beta)

ans =

    1.6821
    0.1938
    0.8898
    1.8185
    2.2447
    0.0067
    1.2273
    0.5525
    2.1314
    1.3443
    0.5279
    0.6278
    0.0077
    0.0336
    0.0189
    0.6735
    0.0526
    0.3976
    0.3386
    0.1828
    0.1465
    0.0681
    0.1227
    0.0244
    0.2254
    0.1542
    0.0217
    0.0091
    0.3787
    0.0115
    0.0817
    0.1218
    0.7409
    1.9097
    0.0519
    0.9462
    0.8698
    0.0632
    0.0430
         0
    1.1810
    0.0000
    0.7544
         0
    1.0332
    1.5796
    0.5866
    4.1280
    0.5862
    0.0484
    1.6571
    0.9258
    0.3386
    0.1425
    0.0451
    0.0210
    0.0236
    0.0108
    0.0215
    0.0379
    0.7172
    0.2374
    0.0636
    0.0183
    0.0485
    0.0355
    0.0185
    0.0323
    0.0145
    0.0470
    0.0222
    0.0005
    0.0555
    0.0107
    0.0185
    0.0000
    0.0156
    0.0128
    0.0438
    0.0028
    0.0000
    0.0000

abs(linSVM.Beta) > .1

ans =

     1
     1
     1
     1
     1
     0
     1
     1
     1
     1
     1
     1
     0
     0
     0
     1
     0
     1
     1
     1
     1
     0
     1
     0
     1
     1
     0
     0
     1
     0
     0
     1
     1
     1
     0
     1
     1
     0
     0
     0
     1
     0
     1
     0
     1
     1
     1
     1
     1
     0
     1
     1
     1
     1
     0
     0
     0
     0
     0
     0
     1
     1
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0
     0

sum(abs(linSVM.Beta) > .1)

ans =

    38

