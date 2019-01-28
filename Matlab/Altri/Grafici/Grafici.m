%% ES 1
x_ax1 = linspace(0,40,500);
x_ax2 = 0:4:40;
plot(x_ax1,x_ax1.*cos(x_ax1),'r-',x_ax2,x_ax2.*cos(x_ax2),'go')
title('Plot of f(x)=xcos(x) and some of its points')
clear x*;
%% ES 2
x_ax = linspace(0,2*pi,5000);
y1 = sin(3*x_ax).^2;
y2 = cos(4*x_ax).^4;
v = abs(y1-1) < 1e-4;
plot(x_ax,y1,x_ax,y2,x_ax(v),y1(v),'o')
legend('sin(3x)^2','cos(4x)^2','sin(3x)^2=1')
clear x_ax y* v
%% ES 3
f = @(x,y) exp(-x.^2-y.^2).*sin(x.*y);
figure(1);
ezmesh(f,[-pi pi])
figure(2);
[X,Y] = meshgrid(linspace(-pi,pi));
Z = f(X,Y);
mesh(X,Y,Z)
figure(3);
contour(X,Y,Z,[1/100,1/100])
title('f(x,y)=1/100')
clear f X Y Z
%% ES 4
hold on
[X,Y] = meshgrid(linspace(-3,3));
Z = ones(100,100);
for p=1:4
    Z = Z + (1/p).*(X+1i.*Y).^p;
    contour(X,Y,abs(Z),[1,1],'color',rand(3,1))
end
legend();
hold off
clear X Y Z p
%% ES 5
[X,Y] = meshgrid(linspace(-2,2));
Z1 = abs(X)+abs(Y);
Z2 = sqrt(X.^2+Y.^2);
Zinf = max(abs(X),abs(Y));
hold on
contour(X,Y,Z1,[1,1],'r')
contour(X,Y,Z2,[1,1],'g')
contour(X,Y,Zinf,[1,1],'b')
legend('Palla norma 1','Palla norma 2','Palla norma infinito')
hold off
clear X Y Z*
%% ES 6
figure()
for l=3:8
    subplot(3,2,l-2)
    plot(nsidedpoly(l))
    axis equal
end
clear l
%% ES 7
n = 5;
A = rand(n,n)+1i*rand(n,n);
es7or8(A)
clear n A
%% ES 8
n = 5;
A = rand(n,n);
es7or8(A+A')
clear n A
%% ES 9
x = 5*sin(linspace(0,2*pi));
y = 2*cos(linspace(0,2*pi));
hold on
for t=[-pi/3 0 pi/3]
    plot(x*cos(t)-y*sin(t),x*sin(t)+y*cos(t),'-b',5*cos(t),5*sin(t),'r*')
end
hold off
title('Rotazioni di ellissi')
clear x y t