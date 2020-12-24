clc;
clear;
clf;
clf reset;

fun = @(x,a) a-x^2; 
x0 = 0; a0 = 0; a1 = 2; N = 1000; L = 200;
mat = yue_bifur(fun,x0,a0,a1,N,L);

ylabel('a');
zlabel('x');

