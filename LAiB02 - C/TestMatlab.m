format long
N = 50;
volte = 1;
voltetot = 100;
res = zeros(voltetot,1);
while volte < voltetot
    A = rand(N);
%if (rank(A)==N) & (cond(A) < 500)
%sprintf("rank(A): %3f, cond(A): %3f",rank(A),cond(A))
    command = "./a.out " + num2str(N);
    for i=1:N
        for j=1:N
            command = command + " " + num2str(A(i,j),20);
        end
    end
    [status,cmdout] = system(command);
    xC = str2num(cmdout)';
    xVera = A\ones(N,1);
    res(volte) = norm(xVera-xC)/norm(xVera);
    volte = volte+1;
%end
end
figure();
semilogy(res,'o','MarkerSize',15);
title('Errore Relativo soluzione sistema lineare C vs MATLAB');
xlabel('Varie Esecuzioni con input casuali');
ylabel('Errore Relativo');