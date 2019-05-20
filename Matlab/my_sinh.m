function [y] = my_sinh(x_true)
%MY_SINH Very clever sinh(x) implementation
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
x = abs(x_true);
y((0<=x)&(x<=22)) = (exp(x)-1+(exp(x)-1)./(exp(x)))/2;


y(x_true<0) = -y(x_true<0);                                   %Finished implementing NOTE1
end

