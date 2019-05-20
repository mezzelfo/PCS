function [output] = naive_sinh(x)
%naive_sinh Compute naively sinh
%   sinh(x) = (exp(x)-exp(-x))/2
output = (exp(x)-exp(-x))./2;
end

