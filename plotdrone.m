function [ x,y ] = plotdrone( r,c,char )
%PLOTDRONE �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��

%PLOTCIRCLE �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
 theta=0:pi/100:2*pi;

x=c(1)+r*cos(theta); y=c(2)+r*sin(theta);
color=rand(1,3);
rho=r*sin(theta);
%plot(c(1),c(2),'*','color',char);
hold on;
plot(x,y,'-','color',char)

hold on; %axis equal

%fill(x,y,'c')




end

