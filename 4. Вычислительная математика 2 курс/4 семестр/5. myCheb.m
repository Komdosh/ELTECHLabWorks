function myCheb(x, myFunc, degree)
    %clc;
    %clear;

    figure(degree+1);
    myLagr(x, myFunc, 1);
    
    a=x(1);
    b=x(end);
    l=degree;
    m=0:l-1;
    xCheb=0.5*((b-a)*cos((2*m+1)/l*0.5*pi)+a+b);
    figure(degree+2);
    myLagr(xCheb, myFunc, 1);
   
    maxDif=zeros(1, degree);
    for l=1:degree
        m=0:l-1;
        xCheb=0.5*((b-a)*cos((2*m+1)/l*0.5*pi)+a+b);
        LCheb=myLagr(xCheb, myFunc, 0);
        T=linspace(x(1), x(end), 100);
        yCheb=polyval(LCheb,T);
        figure(l);
        plot(T,yCheb);
        y=myFunc(T);
        for i=1:length(yCheb)
            if(maxDif(l)<abs(y(i)-yCheb(i)))
               maxDif(l)=abs(y(i)-yCheb(i));
            end
        end
    end

    td=0:degree-1;
    figure(degree+3);
    plot(td, maxDif, 'b');
    grid;
end
