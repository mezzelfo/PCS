%% ES 1
format long
x = ones(1,100)*10^-9;
x(1)=10^8;
sum(x)
sum(sort(x))
clear x
%% ES 2,3
myeps = 1.0;
t=0;
while((1.0+myeps)>1.0)
    myeps = myeps/2;
    t = t+1;
end
t = t-1
myeps = 2*myeps
eps
clear myeps t
%% ES 4
format long
a = 1.0;
delta = [1e-1 1e-8 1e-12];
x1 = a + sqrt(a^2-delta)
x2 = a - sqrt(a^2-delta)
x2v2 = delta./x1
abs(x2-x2v2)./x2
clear a delta x*
%% ES 5
[xmin,p] = es5a()
[xmax,t] = es5b()
clear x* p t