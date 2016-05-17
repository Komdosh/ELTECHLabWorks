function N = myNewton(X, Y, myFunc)
    %clc;
    clearvars -except X Y myFunc xx;
    lenX = length(X);
    if(isvector(X)>1)
        error('X должно быть вектором!')
    else
        if(isvector(Y)>1)
            error('Y должно быть вектором!')
        else
            if(lenX~=length(Y))
                error('Вектора должны иметь один и тот же размер!')
            end
        end
    end
    
    dif = Y;
    for j = 2:lenX 
        back=dif(j-1);
        for i=j:lenX 
            temp = dif(i);
            dif(i) = dif(i)-back;
            back = temp;
        end
    end

    for i = 2:length(dif)
         dif(i) = dif(i)/factorial(i-1);
    end
    N=0;
    for j=1:lenX-1
      P=1;
      for i=1:j
        P = conv(P,[1,-X(i)]);
      end 
      N = P*dif(j+1)+[0, N];
    end
    N(end) = N(end)+Y(1);
    
    T=linspace(X(1), X(end), 100);
    Y0 = myFunc(T);
    Y1 = polyval(N, T);
    
    plot(T, Y0, 'g', T, Y1, 'r');
    grid;
end
