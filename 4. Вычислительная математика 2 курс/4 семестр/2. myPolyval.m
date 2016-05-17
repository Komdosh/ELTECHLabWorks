function C = myPolyval(p, x)
    clc;
    clearvars -except p x;
    if ~(isvector(p) || isempty(p))
        error('Нет, давайте первым аргументом вектор');
    end
    sizeX = size(x);
    k = x;
    C = zeros(sizeX(1), sizeX(2));
    C(:) = p(end);
    lenP = length(p);
    for i = lenP-1:-1:1
        C = C + k*p(i);
        k = k.*k;
    end
