%   Se f(x)=x^3, applicando il cubo di binomio la differenza divisa è:
%   
%   f(x0+h)-f(x0)   h^3 + 3*h^2*x0 + 3*h*x0^3 + x0^3 - x0^3
%   ------------- = --------------------------------------- = h^2 + 3*h*x0 + 3*x0^2
%        h                            h

differenzaDivisa = @(x0,h) ((x0+h).^3-(x0).^3)./h;
differenzaDivisaNoErr = @(x0,h) h.^2 + 3.*h.*x0 + 3.*x0.^2;
derivata = @(x0) 3.*x0.^2;
x_ax = 10.^(1:4);
ea = abs(differenzaDivisa(x_ax,10^-7)-derivata(x_ax));
eaNE = abs(differenzaDivisaNoErr(x_ax,10^-7)-derivata(x_ax));
er = ea./derivata(x_ax);
erNE = eaNE./derivata(x_ax);
% Plot error of x^3
title('Grafici degli errori di varie implementazioni per la differenza divisa')
xlabel('Log scale of values from 10 to 10000')
yyaxis left
loglog(x_ax,ea,'*-',x_ax,eaNE,'o-');
ylabel('Absolute error (log scale)')
yyaxis right
loglog(x_ax,er,'*-',x_ax,erNE,'o-');
ylabel('Relative error (log scale)')

%   Se f(x)=x^5, applicando il cubo di binomio la differenza divisa è:
%   
%   f(x0+h)-f(x0)   
%   ------------- = ... = h^5 + 5*h^3*x0 + 10*h^2*x0^2 + 10*h+x0^3+5*x0^4
%         h

differenzaDivisa = @(x0,h) ((x0+h).^5-(x0).^5)./h;
differenzaDivisaNoErr = @(x0,h) h.^4 + 5.*(h.^3).*x0 + 10.*(h.^2).*(x0.^2) + 10.*h.*x0.^3 + 5.*x0.^4;
derivata = @(x0) 5.*x0.^4;
x_ax = 10.^(1:4);
ea = abs(differenzaDivisa(x_ax,10^-7)-derivata(x_ax));
eaNE = abs(differenzaDivisaNoErr(x_ax,10^-7)-derivata(x_ax));
er = ea./derivata(x_ax);
erNE = eaNE./derivata(x_ax);
% Plot error of x^5
figure();
title('Grafici degli errori di varie implementazioni per la differenza divisa')
xlabel('Log scale of values from 10 to 10000')
yyaxis left
loglog(x_ax,ea,'*-',x_ax,eaNE,'o-');
ylabel('Absolute error (log scale)')
yyaxis right
loglog(x_ax,er,'*-',x_ax,erNE,'o-');
ylabel('Relative error (log scale)')