svms = {libSVMStructrbf10, libSVMStructrbf11, libSVMStructrbf12};
for i = 1:3
    temp = SVMStruct;
    SVMStruct = svms{i};
    evaluateSVM;
    SVMStruct = temp;
end
