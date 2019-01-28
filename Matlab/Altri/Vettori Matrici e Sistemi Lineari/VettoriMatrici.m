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
figure()
spy(A)
figure()
spy(U)
%% ES 5
for n=10:10000:30000
    A = 10*diag(ones(n,1));
    A = A + 5*diag(ones(n-1,1),-1);
    A = A + 5*diag(ones(n-1,1),+1);
    A = A + diag(ones(n-9,1),-9);
    A = A + diag(ones(n-9,1),+9);
    whos A
end
clear A n
%% ES 6
for n=10:10000:50010
    e=ones(n,1);
    A = spdiags([e 5*e 10*e 5*e e], [-9 -1 0 1 9], n, n);
    whos A
end
clear A n e
%% ES 7
n = 10;
c = -5;
A = 4*diag(ones(n,1))-diag(ones(n-1,1),-1)-diag(ones(n-1,1),1);
B = [eye(n/2);eye(n/2)];
C = c*eye(n/2);
[A B; B' C]
clear n c A B C
%% ES 12
q = 3;
p = 2;
n = 10;
A = (p+q)*eye(n)+spdiags(rand(n,p+q+1),-q:p, n, n);
[L,U] = lu(A);
A
L
U
clear A L U q p n
%% ES 13
n = 10;
A = 2*eye(n)+spdiags(rand(n,3),-1:1, n, n);
rref(A)
clear A n