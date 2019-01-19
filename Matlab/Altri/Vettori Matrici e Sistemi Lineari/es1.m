function [] = es1(A,x)
%ES1 Plot of vector x and vector Ax
%   A is 2x2 real matrix, x is a 2-component vector
v = A*x;
figure()
hold on
subplot(1,2,1)
plot([0,x(1)],[0,x(2)],'g-',x(1),x(2),'gv')
title('Vector x')
axis([-2 2 -2 2])
subplot(1,2,2)
plot([0,v(1)],[0,v(2)],'g-',v(1),v(2),'gv')
title('Vector Ax')
axis([-2 2 -2 2])
hold off
end

