function m = subsValues(m, oldCode, newCode )
%substitutes the values from oldCode present in m with
%the corresponding element in newCode,  oldCode should be the same length
%as newCode

[a,b] = ismember(m,oldCode);
m(a) = newCode(b(a));
end

