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



function [ c1, c2, c3, c4, c5 ] = analyzeWindFarm( filenameWind, ...
    filenameWave, filenameBuoy, windSpeedMin, windSpeedMax, ...
    waveHeightMax, waveHeightRisk, deckHeight )
% Function to complete Task 1. Evaluates the 5 constraints on the location of a
% wind farm.
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
%         waveHeightMax: for constraints 2 & 3 -- maximum wave height (m)
%        waveHeightRisk: for constraint 3 -- maximum wave height risk (%)
%            deckHeight: for constraint 4 -- height of the deck that supports 
%                        the turbine base (m)
%
%   return values:
%                    c1: boolean values corresponding to whether the wind 
%                        farm location passes constraint #1
%                    c2: boolean values corresponding to whether the wind 
%                        farm location passes constraint #2
%                    c3: boolean values corresponding to whether the wind 
%                        farm location passes constraint #3
%                    c4: boolean values corresponding to whether the wind 
%                        farm location passes constraint #4
%                    c5: boolean values corresponding to whether the wind 
%                        farm location passes constraint #5

%load all csv file
    
    fileWind = csvread(filenameWind);
    fileWave = csvread(filenameWave);
    fileBuoy = csvread(filenameBuoy,1,1,[1,1,1,2]);
   
% constraint 1
% pull out individual lat and lon
   
    latBuoy = fileBuoy(1);
    longBuoy = fileBuoy(2);
    windMin = fileWind(latBuoy,longBuoy) >= windSpeedMin;
    windMax = fileWind(latBuoy,longBuoy) <= windSpeedMax;
    c1 = windMax & windMin;

%constraint 2 (average wave height)
    c2 = (fileWave(latBuoy,longBuoy) <= waveHeightMax);

%constraint 3 (read only the wave height)
    waveHeight = csvread(filenameBuoy,5,1,[5,1,342,1]);
    c3 = sum(sum(waveHeight < waveHeightMax)) ./ numel(waveHeight) > waveHeightRisk ./100;

%constraint 4
% rwh = rogue wave height
    rwh = 2 .* waveHeight;
    c4 = all(rwh < deckHeight);

%constraint 5 (standard deviation of wave)
    stdWave = std(waveHeight);
    c5 = stdWave < 0.05 .* fileWave(latBuoy,longBuoy);
    
end