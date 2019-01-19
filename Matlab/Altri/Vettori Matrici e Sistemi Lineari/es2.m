function [] = es2(A,x)
%ES1 Plot of vector x and vector Ax
%   A is 3x3 real matrix, x is a 3-component vector
v = A*x;
figure()
hold on
plot3([0,x(1)],[0,x(2)],[0,x(3)],'g')
plot3([0,v(1)],[0,v(2)],[0,v(3)],'r')
plot3(x(1),x(2),x(3),'gv')
plot3(v(1),v(2),v(3),'rv')
legend('x','Ax')
hold off
grid on
view(3)
end

