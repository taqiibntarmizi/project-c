% taqiuddin
% none 
% 024
% 10/08/2023

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 4d56ac82-3232-4493-bb2f-f76ce9e60751
%------------------------------------------------------


function [  ] = makePlots( filenameWind, filenameWave, filenameBuoy, ...
    windSpeedMin, windSpeedMax, waveHeightMax )

%   Function to complete Task 2. Creates a figure with multiple plots that 
%   summarizes the environmental conditions for a wind farm.  Saves figure as 
%   a .png file.
%
%   parameters: 
%          filenameWind: a string that names the file containing the 
%                        global-model-based average wind speed 
%                        (i.e. 'windSpeedTestCase.csv')
%          filenameWave: a string that names the file containing the 
%                        global-model-based average global wave heights 
%                        (i.e. 'waveHeightTestCase.csv')
%          filenameBuoy: a string that names the file containing the time 
%                        series of wave heights measured by the buoy          
%                        (i.e. 'buoyTestCase.csv')
%          windSpeedMin: for constraint 1 -- minimum wind speed (m/s)
%          windSpeedMax: for constraint 1 -- maximum wind speed (m/s)
%         waveHeightMax: for constraint 2 -- maximum wave height (m)
%
%   return values: none
%
%   notes:
%       Feel free to use different variable names than these if it makes 
%       your code more readable to you.  These are internal to your 
%       function, so it doesn't matter what you call them.

%% Load the data

% Get lat/lon data
    lon = csvread('lon.csv');    
    lat = csvread('lat.csv');
    

% Read in the rest of the data you need...
    fileWind = csvread(filenameWind);
    fileWave = csvread(filenameWave);
    fileBuoy = csvread(filenameBuoy,1,1,[1,1,1,2]);  %getting the buoy lat and lon only

% plot 1
    subplot(3,2,1)
    [lon1,lat1] = meshgrid(lon,lat);
    contourf(lon1,lat1,fileWind,'LineStyle','none');
    colorbar;
    title('Average Wind Speed (m/s) Across Planet');
    ylabel('latitude (deg)');
    xlabel('longitude (deg)');

%plot 2
    subplot(3,2,2);
    contourf(lon1,lat1,fileWave,'LineStyle','none');
    title('Average Wave Height (m) Across Planet');
    colorbar;
    title('Average Wave Height (m) Across Planet');
    ylabel('latitude (deg)');
    xlabel('longitude (deg)');

%plot 3
    subplot(3,2,3);
    c1 = fileWind >= windSpeedMin & fileWind <= windSpeedMax;
    c2 = (fileWave <= waveHeightMax);
    true = c1 & c2;
    fileWind(true) = 1;
    fileWind(~true) = 0;
    contourf(lon1,lat1,fileWind,'LineStyle','none');
    ax = gca;
    c = flipud(gray);
    colormap(ax,c);
    title('Potential Wind Farm Locations');
    xlabel('longitude (deg)');
    ylabel('latitude (deg)');

% create red sqaure mark on the lot and lan on the same graph

    hold on

    lat3 = lat(fileBuoy(1));
    lon3 = lon(fileBuoy(2));
    scatter(lon3, lat3, 200, "red","square",'LineWidth',3);
 
    hold off

%plot 4 wave height at buoy location
    subplot(3,2,4);
    buoyWaveHeight = csvread('buoyTestCase.csv',5,1,[5,1,342,1]);
    histogram(buoyWaveHeight);
    title('Wave Heights at Buoy Location');
    xlabel('wave height (m)');
    ylabel('number of occurrences');
    grid on

%plot 5
    subplot(3,2,[5,6]);
    yAxis = buoyWaveHeight;
    time = csvread("buoyTestCase.csv",5,0, [ 5,0,342,0 ]);
    xAxis = time;

%Average Wave Height(take the lat and lon and index it into fileWave
    latx = fileBuoy(1);
    lonx = fileBuoy(2);
    avg = fileWave(latx,lonx);
    plot(xAxis,yAxis, xAxis, avg*ones(size(xAxis)));

    title('Wave Height Comparison: Global to Local');
    xlabel('time (hours)');
    ylabel('wave height (m)');
    legend('Buoy-measured','Global average');
    grid on
    print('environmentalSummary.png', '-dpng' );

end