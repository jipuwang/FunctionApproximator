% if input the degree of the polynomial F(X)=X^2;
global a b;

J=20;
Z=10;
delta=Z/J;
X_j=linspace(0,Z,J+1);

F_j=zeros(J,1);
F_j_hat=zeros(J,1);
b=zeros(J,1);
a=zeros(J,1);


% for a quadratic case
for j=1:J
    F_j(j)=((j-1)*(j-1)+(j-1)*j+j*j)*delta*delta/3;
    F_j_hat(j)=(j-1+j)*((j-1)*(j-1)+j*j)*delta*delta*delta/4;
end

% for a polynomial of degree n
f1= @(X) X.^2;
f2= @(X) X.^3;
for j=1:J
    lb=(j-1)*delta;
    ub=j*delta;
    F_j(j)=ners590NumIntegrator(lb,ub,f1)/delta;
    F_j_hat(j)=ners590NumIntegrator(lb,ub,f2)/delta;
end

b=F_j;
for j=1:J
    a(j)=(F_j_hat(j)-b(j)*(j-1+j)*delta/2)*12/delta/delta;
end

ners590Plotter
%% Error evaluator
aeraError=zeros(J,1);
for j=1:J
    lb=(j-1)*delta;
    ub=j*delta;
    mid=(lb+ub)/2;
    fErr= @(X) X.^2-a(j)*(X-mid)-b(j);
    aeraError(j)=ners590NumIntegrator(lb,ub,fErr);
end

aa=1;





