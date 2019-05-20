clc
x_ax = 10.^(-12:0);
y_true = sinh(x_ax);
y_naive = naive_sinh(x_ax);
err_ass = abs(y_true-y_naive);
err_rel = err_ass./y_true;
% Plot the errors of a naive sinh(x) implementation
title('Errors plot of a naive sinh(x) implementation')
xlabel('Log scale of values from 10^{-12} to 10^0')
yyaxis left
semilogx(x_ax,err_ass,'o');
ylabel('Absolute error')
yyaxis right
loglog(x_ax,err_rel,'*');
ylabel('Relative error (log scale)')

% Plot also my implementation of sinh(x)
figure();
y_my = my_sinh(x_ax);
err_ass_my = abs(y_true-y_my);
err_rel_my = abs(err_ass_my./y_true);
loglog(x_ax,err_rel_my,'*',x_ax,err_rel,'o')
legend('Relative Error of my impl.','Relative Error of Naive impl.')
