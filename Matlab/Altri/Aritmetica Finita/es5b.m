function [xmax,r] = es5b()
%ES5B Ritorna il più grande numero diverso da inf della forma 2^r
%   Detailed explanation goes here
x = 1.0;
p=0;
while(x~=inf)
    x = x*2;
    p = p+1;
end
r = p-1;
xmax = 2^r;
end
