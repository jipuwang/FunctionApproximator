%ners590linearizeSin(X)
% if input the degree of the polynomial F(X)=X^n;
global a b;

J=20;
Z=10;
delta=Z/J;
X_j=linspace(0,Z,J+1);

F_j=zeros(J,1);
F_j_hat=zeros(J,1);
b=zeros(J,1);
a=zeros(J,1);

% for a sin(X) function 
for j=1:J
    Xinit=(j-1)*delta;
    Xend=j*delta;
    F_j(j)=(sin(Xend)-sin(Xinit))/delta;
    F_j_hat(j)=(cos(Xend)-cos(Xinit)+(Xend)*sin(Xend)-(Xinit)*sin(Xinit))/delta;
end

b=F_j;
for j=1:J
    a(j)=(F_j_hat(j)-b(j)*(j-1+j)*delta/2)*12/delta/delta;
end

ners590Plotter
hold on;
fplot(@(x) cos(x),[0 10],'r')