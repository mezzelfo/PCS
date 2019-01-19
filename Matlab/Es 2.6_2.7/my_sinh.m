function [output] = my_sinh(x_true)
%MY_SINH Very clearver sinh(x) implementation
%   Different implementation for different x values ranges (for x in Reals)
%

%   NOTE1: sinh(-x) = -sinh(x)                       ;sinh is an odd function
%   NOTE2: sinh(x) -> exp(x)/2 for x -> +inf         ;The limit is g(x)=exp(x)/2
%   NOTE3: |g(x)-sinh(x)| < k ==> x > ln(1/2k)       ;The absolute error of the approssimation is easely controllable
%   NOTE4: aer(x)/sinh(x) < k ==>  x > ln(1+1/k)/2   ;Also the relative error is therefore easely controllable
%   NOTE5: sinh(x) > k => g(x) > k => x > log(2k)    ;The overflow control can be easely implemented

%   DEDUCE4: k := eps  ==> for all x > ln(1+1/k)/2 the relative error is less then eps 

%                      asse x: (0,+inf)
%   +------------+------------+---------------------...--+----------+
%   | Polynomial |    Naive   |       g(x)=exp(x)/2      | Overflow |
%   +------------+------------+---------------------...--+----------+
%   |            |            |                          |          |
%   +------------+------------+---------------------...--+----------+
%
%
x = abs(x_true);                                                        %Partially implement NOTE1
output = (exp(x)-exp(-x))./2;                                           %Naive Implementation is provided as base case
x_tmp = x(x<(5040*eps)^(1/7));                                          %Support vector for taylor series
output(x<(5040*eps)^(1/7)) = x_tmp+(x_tmp.^3)./6+(x_tmp.^5)./120;       %Taylor Series
output(x>log(1+1/eps)/2) = exp(x(x>log(1+1/eps)/2))./2;                 %Implemented DEDUCE4
output(x>log(2*realmax)) = inf;                                         %Implemented NOTE5

output(x_true<0) = -output(x_true<0);                                   %Finished implementing NOTE1
end

