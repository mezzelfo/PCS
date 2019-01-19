%% ES 1
x = rand(2,1);
A = rand(2,2);
es1(A,x)
t = pi/3;
x = [1;1];
A = [cos(t) sin(t); -sin(t) cos(t)];
es1(A,x)
A = [1 1; 0 2];
es1(A,x)
clear t v A x
%% ES 2
x = [1;2;3];
A = [0 1 2; 0 1 3; 5 -1 0];
es2(A,x)
clear A x
%% ES 3
A = [1 1; 0 2];
es3(A)
A = (-1/4)*A;
es3(A)
A = [1 2; 4 8];
es3(A)
clear A
%% ES 4
A = es4(10,4);
[L,U] = lu(A);
spy(A-U)
%% ES 5
clc
for n=10:10000:50000
    A = 10*diag(ones(n,1));
    A = A + 5*diag(ones(n-1,1),-1);
    A = A + 5*diag(ones(n-1,1),+1);
    A = A + diag(ones(n-9,1),-9);
    A = A + diag(ones(n-9,1),+9);
    whos A
end
clear A n