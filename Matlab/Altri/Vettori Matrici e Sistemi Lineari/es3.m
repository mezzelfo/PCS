function [] = es3(A)
%ES3 Summary of this function goes here
%   Detailed explanation goes here
vs = zeros(100,2);
vsA = zeros(100,2);
i = 1;
for t=linspace(0,2*pi)
    v = [sin(t);cos(t)];
    vs(i,:) = v;
    vsA(i,:) = A*v;
    i = i+1;
end
figure();
subplot(2,1,1)
scatter(vs(:,1),vs(:,2))
title('Sfera unitaria in norma euclidea')
axis equal
subplot(2,1,2)
scatter(vsA(:,1),vsA(:,2))
title('Applicazione di A alla sfera unitaria in norma euclidea')
axis equal


end

