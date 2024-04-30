clear all;
close all;
clc;
objyz=load('../data/obj_locate.txt');
objyz=objyz';
fcm=load('../data/obj_fcm_result.txt');
fcm=fcm';
%cut y and z
yn=10;
zn=10;
objy=objyz(1:2,:);
objz=objyz(3:4,:);
fcmyc=fcm(1:2,1:yn);
fcmyr=fcm(3,1:yn);
fcmzc=fcm(1:2,yn+1:yn+zn);
fcmzr=fcm(3,yn+1:yn+zn);
figure(1)
axis equal;
plot(objy(1,:),objy(2,:),'r.')
%hold on;
%plot(objz(1,:),objz(2,:),'b.')
hold on;
fcmyr=fcmyr';
fcmyc=fcmyc';
for i=1:yn
    if fcmyr(i)>0
    plotcircle(fcmyr(i),fcmyc(i,:));
    end
end
figure(2)
axis equal;
plot(objz(1,:),objz(2,:),'b.')
hold on;
fcmzr=fcmzr';
fcmzc=fcmzc';
for i=1:zn
    if fcmzr(i)>0
    plotcircle(fcmzr(i),fcmzc(i,:));
    end
end