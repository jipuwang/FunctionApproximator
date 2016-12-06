function []=ners590Plotter(midPoints,zeroMom,firstMom)
%% Example also as optional param
global a b;
N=16;
[mu_n,weight_n]=lgwt(N,-1,1); mu_n=flipud(mu_n);

if ~exist('zeroMom','var')
   % zeroMom parameter does not exist, so default it to something
    zeroMom =b;
%     [
%    0.000000520833333
%    0.000032812500000
%    0.000346354166667
%    0.001753645833333
%    0.006004687500000
%    0.016161979166667
%    0.036975520833333
%    0.075257812500000
%    0.140258854166667
%    0.244041145833333
%    0.401854687500000
%    0.632511979166667
%    0.958763020833333
%    1.407670312500000
%    2.010983854166667
%    2.805516145833333
%    3.833517187500000
%    5.143049479166667
%    6.788363020833333
%    8.830270312500000
%              ]*1e4;
end
if ~exist('firstMom','var')
   % firstMom parameter does not exist, so default it to something
    firstMom =   a;
%     [
% 
%    0.000004464285714
%    0.000179464285714
%    0.001279464285714
%    0.004804464285714
%    0.013004464285714
%    0.028879464285714
%    0.056179464285714
%    0.099404464285715
%    0.163804464285710
%    0.255379464285710
%    0.380879464285722
%    0.547804464285693
%    0.764404464285693
%    1.039679464285704
%    1.383379464285728
%    1.806004464285867
%    2.318804464285635
%    2.933779464285728
%    3.663679464286007
%    4.522004464285635
%               ]*1e4; %0.617876244402644 is mu_n(5)
end

if ~exist('midPoints','var')
    % midPoints parameter does not exist, so default it to something
    n=size(zeroMom,1);
    Tau=10;
    startMidpoint=Tau/n/2;
    endMidpoint=Tau-startMidpoint;
    midPoints =linspace(startMidpoint,endMidpoint,n)';
end

%% Plotter
nPt=max(size(midPoints,1),size(midPoints,2));
% you'll have a plot that have 2*nPt
% now generating the X's
deltaX=midPoints(2)-midPoints(1);
X=zeros(2*nPt,1);
Y=zeros(2*nPt,1);
for i=1:nPt
    X(2*i-1)=(i-1)*deltaX;
    X(2*i)=i*deltaX;
end

for i=1:nPt
    Y(2*i-1)=zeroMom(i)-0.5*deltaX*firstMom(i);
    Y(2*i)=zeroMom(i)+0.5*deltaX*firstMom(i);
end
figure(100)
hold on;
for i=1:nPt
    plot([X(2*i-1),X(2*i)],[Y(2*i-1),Y(2*i)],'b-*');
end
% add breakpoint here if you want to debug.
notUsedVariable=0;

%% verify
calcZeroMom=zeros(nPt,1);
calcFirstMom=zeros(nPt,1);
for i=1:nPt
    calcZeroMom(i)=(Y(2*i-1)+Y(2*i))*0.5;
    calcFirstMom(i)=(Y(2*i)-Y(2*i-1))/(X(2*i)-X(2*i-1));
end

display(calcZeroMom-zeroMom);
display(calcFirstMom-firstMom);

 