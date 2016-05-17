function mySpline(x, myFunc)
    %clc ;
    %clear ;
    y = myFunc(x)
    % h vector
    h = (x(2:end)-x(1:end-1));
    maxDif=zeros(1, length(x)-1);
    alpha = zeros(1, length(x)-1);
    % number of splines
    for n = 3:length(x)-1

        % compute ci: C*c = f ==> c = inv(C)*f ;
        C = zeros(n+1,n+1);

        C(1,1) = -2/3*h(1);
        C(1,2) = -1/3*h(1);
        for k=2:n
            C(k,k-1) = h(k-1);
            C(k,k)   = 2*(h(k-1)+h(k));
            C(k,k+1) = h(k);
        end
        C(n+1,n) = 1/3*h(n);
        C(n+1,n+1) = 2/3*h(n);
        % b vector
        f = zeros(n+1,1);
        for k=2:n
            f(k) = ((y(k+1)-y(k))/h(k)-(y(k)-y(k-1))/h(k-1))*3;
        end
        
        b = C\f; %inverse matrix C and multiply on f (inv(C)*f)
        d = y(1:n);

        c = zeros(n,1);
        for k=1:n
            c(k) = (y(k+1)-y(k))/h(k)-h(k)/3*(b(k+1)+2*b(k));
        end

        a = zeros(n,1);
        for k=1:n
            a(k) = (b(k+1)-b(k))/(3*h(k));
        end

        hold off;
        plot(x,y,'b+'); grid; 
        hold on;
        
        for i=1:n
            stepX = 0.1*(x(i+1)-x(i));
            cx = x(i):stepX:x(i+1);
            cy = zeros(1, length(cx));
            y1 = myFunc(cx);
            for k=1:length(cx)
                xc = stepX*(k-1);
                cy(k) = a(i)*xc^3 + b(i)*xc^2+c(i)*xc+d(i);
            end
            for k = 1:length(cx)
                if(maxDif(i)<abs(y1(k)-cy(k))) 
                  maxDif(i)=abs(y1(k)-cy(k));
                  alpha(i) = maxDif(i)/n;
                end
            end
            plot(cx,y1,'g',cx,cy,'r');
        end
    
    end
    hold off;
    td=0:length(maxDif)-1;
    figure(2);
    plot(td, maxDif, 'b');
    figure(3);
    plot(td, alpha, 'b');
end
