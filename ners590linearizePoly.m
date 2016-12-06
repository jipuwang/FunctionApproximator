% if input the degree of the polynomial F(X)=X^n;
global a b;
n=0;

J=20;
Z=10;
delta=Z/J;
X_j=linspace(0,Z,J+1);

F_j=zeros(J,1);
F_j_hat=zeros(J,1);
b=zeros(J,1);
a=zeros(J,1);

% for a polynomial of degree n
for j=1:J
    F_j(j)=(j^(n+1)-(j-1)^(n+1))*delta^(n+1)/(n+1)/delta;
    F_j_hat(j)=(j^(n+2)-(j-1)^(n+2))*delta^(n+2)/(n+2)/delta;
end

b=F_j;
for j=1:J
    a(j)=(F_j_hat(j)-b(j)*(j-1+j)*delta/2)*12/delta/delta;
end

ners590Plotter

