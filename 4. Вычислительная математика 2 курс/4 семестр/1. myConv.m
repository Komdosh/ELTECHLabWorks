% function ans=myConv(A,B) 
% clc;
% clearvars -except A B;
% if(isvector(A)>1)
%     error('A должно быть вектором!')
% else
%     if(isvector(B)>1)
%         error('B должно быть вектором!')
%     end
% end
% ans = zeros(1, length(A)+length(B)-1);
% for i=1:length(A)
%     for j=1:length(B)
%         ans(i+j-1)=ans(i+j-1)+A(i)*B(j);
%     end
% end
% ans
% end

function C=myConv(A,B) 
 clc;
 clearvars -except A B;
 if(isvector(A)>1)
     error('A должно быть вектором!')
 else
    if(isvector(B)>1)
         error('B должно быть вектором!')
     end
 end
 lenA = length(A); 
 lenB = length(B);
 C = zeros(1,lenA+lenB-1);
 for k = 1:lenA+lenB-1
  ix = min(k,lenA); 
  jx = min(k,lenB);
  C(k) = sum(A(k+1-jx:ix).*B(jx:-1:k+1-ix));
 end
 
 C