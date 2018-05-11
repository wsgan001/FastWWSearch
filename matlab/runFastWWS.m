function [bestWin, nns, errors] = runFastWWS(dataName)
clc; close all;
if nargin < 1
    [Train, TrainClass, ~, ~] = loadData();
else
    fprintf('Loading %s data\n', dataName);
    [Train, TrainClass, ~, ~] = loadData(dataName);
end
profile on
tic;
[bestWin, nns, errors] = fastWWSearch(Train, TrainClass);
fastWWSTime = toc;
fprintf('FastWWSearch completed in %.3fs\n', fastWWSTime);
profile viewer

% plot
x = linspace(0, length(errors)-1, length(errors));
figure(1)
clf
plot(x, errors, 'linewidth', 2);
hold on;
plot(bestWin, errors(bestWin+1), 'rx', 'MarkerSize', 8);
hold off;
xlim([0, length(errors)]);
ylim([0, 1]);
xlabel('Warping Windows, w')
ylabel('Error Rate, e');
title(sprintf('Error Rate vs Warping Window - %d', bestWin))

end