function [ x,y ] = plotcircle( r,c)
%PLOTCIRCLE 此处显示有关此函数的摘要
%   此处显示详细说明
 theta=0:pi/100:2*pi;

x=c(1)+r*cos(theta); y=c(2)+r*sin(theta);
color=rand(1,3);
rho=r*sin(theta);
plot(c(1),c(2),'*','color',color);
hold on;
plot(x,y,'-','color',color)

hold on; %axis equal

%fill(x,y,'c')

end

