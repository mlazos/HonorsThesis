function o = findimseg( name, imsegs )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
o = find(arrayfun(@(x)all(strcmp(x.imname,name) == 1), imsegs) == 1);

end

