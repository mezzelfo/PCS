function [] = es7or8(A)
%ES7 Cerchi di Gershgorin
% Cerchi di Gershgorin Plot
    
    n = size(A,1);

    if issymmetric(A)
        hold on
        for i=1:n
            x0=real(A(i,i));
            r = 0;
            for j=1:n
                if i~=j
                    r = r + abs(A(i,j));
                end
            end
            plot([x0-r,x0+r],[i,i],'-v',x0,i,'+');
        end
        axis equal
        hold off
        title('Cerchi-riga di Gershgorin nel Reale')
    else
        ang=linspace(0,2*pi);
        hold on
        for i=1:n
            x0=real(A(i,i));
            y0=imag(A(i,i));
            r = 0;
            for j=1:n
                if i~=j
                    r = r + abs(A(i,j));
                end
            end
            
            xp=r*cos(ang);
            yp=r*sin(ang);
            plot(x0+xp,y0+yp,x0,y0,'+');
        end
        axis equal
        hold off
        title('Cerchi-riga di Gershgorin')
    end
    
end

