%% ES 1
n = 10^7;
x = [];
tic
for i=1:n
    x(i)=i;
end
toc
tic
y = zeros(1,n);
for i=1:n
    y(i)=i;
end
toc
clear i x n y
%% ES 2
n = 500;
t = [0 0 0];

for v=1:2000
    A = rand(n,n);
    b = rand(n,1);
    c = zeros(n,1);

    %Primo modo: due cicli for
    tic
    for i=1:n
        for j=1:n
            c(i) = c(i) + b(j)*A(i,j);
        end
    end
    t(1) = t(1) + toc;

    %Secondo modo: un ciclo for
    tic
    for i=1:n
        c(i) = A(i,:)*b;
    end
    t(2) = t(2) + toc;

    %Secondo modo: un ciclo for
    tic
    c = A*b;
    t(3) = t(3) + toc;
end
t
clear A b n c i j t
%% ES 3
n=100;
v=char(randi(126-32,[n,2])+32);
t=zeros(n,1);
for volte=1:100000
    for pos=1:n
        cercata = v(pos);
        tic;
        for test=1:n
            if v(test)==cercata
                t(pos) = t(pos) + toc;
                break;
            end
        end
    end
end
plot(t,'o')
clear n v i s t volte cercata pos test
