clear all
clc
nmax = 10;
volteTot = 10000;
stepn = nmax/10;
stepq = stepn;
n_ax = stepn:stepn:nmax;
tDensa = zeros(nmax,1);
tOpt = zeros(nmax);

for volte=1:volteTot
    for n = n_ax
        A = rand(n,n);
        tic;
        lu(A);
        tDensa(n) = tDensa(n) + toc;
        for q=stepq:2*stepq:(n-stepq)
            p = n-q;
            A11 = A(1:p,1:p);
            A22 = A(p:n,p:n);
         
            tic;
            lu(A11);
            lu(A22);
            tOpt(n,q) = tOpt(n,q) + toc;
        end
    end
end
hold on
yyaxis left
plot(n_ax,tDensa(n_ax),'-*')
for q=stepq:2*stepq:(nmax-stepq)
    local_n = n_ax(n_ax>q);
    plot(local_n,tOpt(local_n,q),'-o','color',rand(3,1))
end
yyaxis right
plot(n_ax,(1/3).*(n_ax.^3),'-o')
hold off
