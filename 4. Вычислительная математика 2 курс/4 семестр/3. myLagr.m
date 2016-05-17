function L=myLagr(X, myFunc, P)
    Y = myFunc(X);
    N = length(X);
    if(isvector(X)>1)
        error('X должен быть вектором!')
    end
    L=zeros(1, N);
    for i=1:N
        L=L+Y(i)*li(X, N, i);
    end
    T=linspace(X(1), X(end), 100);
    Y0 = myFunc(T);
    Y1 = polyval(L, T);
    if(P)
        plot(T, Y0, 'g', T, Y1, 'r');
        grid;
    end
end

function B=li(X, N, i)
    B = 1;
    for j=1:N
         if j~=i
            B=conv(B,[1/(X(i)-X(j)),-X(j)/(X(i)-X(j))]);
         end
    end
end
   
