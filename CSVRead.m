data = csvread('sampleCSV.dat'); %import csv
%use each column of data to create two arrays of angle, and one of length
for i = 1:(length(data));
    theta(i)= data(i, 1)*(pi/180)
    elevation(i)= data(i, 2)*(pi/180);
    radius(i)= data(i, 3);
end
%convert angles and radius to cartesian coordinates
[x,y,z] = sph2cart(theta,elevation,radius)
%plot cartesian coordinates
scatter3(x,y,z)