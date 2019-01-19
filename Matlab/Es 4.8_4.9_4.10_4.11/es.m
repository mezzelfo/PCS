clear all
clc
warning('off','MATLAB:singularMatrix')
n=100;
step=n/20;
x_true = ones(n,1);
t = zeros(n,1);
x_ax = step:step:n;
for volte=1:10
    Ar = rand(n,n);
    for q=x_ax
        p = n-q;
        A = Ar;
        %A(q:n,1:p) = 0;
        b = A*x_true; 
        tic;
        x = A\b;
        t(q) = t(q) + toc;
    end
end
t2 = t(x_ax);
yyaxis left
plot(x_ax,t2,'-*')
yyaxis right
plot(x_ax,(1/3).*(x_ax.^3),'-o')
warning('on','MATLAB:singularMatrix')
