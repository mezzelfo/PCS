function [A] = es4(N,alfa)
%ES4 Summary of this function goes here
%   Detailed explanation goes here
A = diag(alfa*ones(1,N))-diag(ones(1,N-1),-1)-diag(ones(1,N-1),+1);
A(1,:) = -1;
A(:,1) = -1;
A(1,1) = N;
end

