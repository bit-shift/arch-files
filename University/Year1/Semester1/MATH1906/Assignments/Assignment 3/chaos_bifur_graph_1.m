% Chaos Bifurcation Graph
% This file sets up the initial parameters that are relevant to our system

% Author Keegan Gyoery

% Clear the command window and the workspace
clear;
clc;

% Clear the figure and the figure properties
clf reset;
clf;

% Initialise the function as the variable f
f = @(x,a) a - x^2; 

% Set the intial parameters
x0 = 0;
a0 = 0; 
a1 = 2; 
N = 1000; 
L = 200;

% Call the function yue_bifur
mat = yue_bifur(f,x0,a0,a1,N,L);

% Hold the bifurcation diagram on
hold on;

% Plot the vertical line on the same graoh at a = 0.75
plot3([0 0],[0.75 0.75],[-2 2]);

% Hold the line on the plot
hold on;

% Plot the vertical line on the same graph at a = 1.25
plot3([0 0],[1.25 1.25],[-2 2]);

% Hold the line on the plot
hold on;

% Plot the vertical line on the same graph at a = 1.357084703
plot3([0 0],[1.366284703 1.366284703],[-2 2]);

% Hold the line on the plot
hold on;

% Plot the vertical line on the same graph at a = 1.386269449
plot3([0 0],[1.393269449 1.393269449],[-2 2]);

% Label the axes
ylabel('a');
zlabel('x');




