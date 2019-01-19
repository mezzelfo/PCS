function [xmin,p] = es5a()
%ES5A Ritorna il più piccolo numero diverso da zero della forma 2^-2
%   Detailed explanation goes here
x = 1.0;
p=0;
while(x~=0)
    x = x/2;
    p = p+1;
end
p = p-1;
xmin = 2^(-p);
end

