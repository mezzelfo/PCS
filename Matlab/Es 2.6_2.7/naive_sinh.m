function [output] = naive_sinh(x)
%MYSINH Compute naively sinh
%   sinh(x) = (exp(x)-exp(-x))/2
output = (exp(x)-exp(-x))./2;
end

