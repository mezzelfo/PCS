n = 10000;
qstep = 500;
tOpt = zeros(n,1);
tEs = zeros(n,1);
tDensa = n^3/3 * ones(n,1);
q_ax = qstep:qstep:n;
for v=1:1
    for q=q_ax
        p = n-q;
        tOpt(q) = q^3/3 + p^3/3;
        A11 = rand(p,p);
        A22 = rand(q,q);
        tic;
        lu(A11);
        lu(A22);
        tEs(q) = tEs(q) + toc;
    end
end
plot(q_ax,tOpt(q_ax),q_ax,tDensa(q_ax),0,0)
yyaxis right
plot(q_ax,tEs(q_ax),'-o',0,0)