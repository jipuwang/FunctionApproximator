%ners590NumIntegrator
function [sum]=ners590NumIntegrator(lb,ub,f)
if ~exist('lb','var')
    lb=1;
end
if ~exist('ub','var')
    ub=2;
end
if ~exist('f','var')
    f = @ners590Square;
end

nPt=100000;
x_j=linspace(lb,ub,nPt+1);
delta_x=(ub-lb)/nPt;

sum=0;
valInit=f(x_j(1));
for iPt=1:nPt
    temp=f(x_j(iPt+1));
    valEnd=temp;
    sum=sum+0.5*delta_x*(valInit+valEnd);
    valInit=valEnd;
end

% sum

