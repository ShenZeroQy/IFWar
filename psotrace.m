clear all;
close all;
clc;
objyz=load('../data/obj_locate.txt');
objyz=objyz';
objy=objyz(1:2,:);
objz=objyz(3:4,:);
psotracey=load('../data/obj_pso_tracey.txt');
psotracez=load('../data/obj_pso_tracez.txt');
psoprize=load('../data/obj_pso_prize.txt');
[my,ny]=size(psotracey);
[mz,nz]=size(psotracez);
mz=my-mz

psoprize=psoprize';
for i=1:length(psoprize)
    psoprize(i)=psoprize(i);
end
figure(2)
plot(psoprize);
title('CPSO任务价值变化曲线')
xlabel('迭代次数')
ylabel('Prize')

for i=1:my
interfacer=1000;
figure(1)
axis equal;

plot(objy(1,:),objy(2,:),'r.')
hold on;
psoonce=psotracey(i,:);
red=[1,0,0];
for j=1:(ny/2)
    plotdrone(interfacer,[psoonce(2*j-1),psoonce(2*j)],red);
end
%close(figure(1));
i=i;
%figure(2)
%axis equal;
plot(objz(1,:),objz(2,:),'b.')
hold on;
psoonce=psotracez(i,:);
blue=[0,0,1];
for j=1:(nz/2)
    plotdrone(interfacer,[psoonce(2*j-1),psoonce(2*j)],blue);
end
%close(figure(2));
title(['第' num2str(i) '轮次']);
saveas(gcf, ['./fig/Cpso' num2str(i)], 'png')
close(figure(1));
i=i
end

