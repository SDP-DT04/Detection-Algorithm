M = load('298_1_Nov15_ios.mat'); 

t = M.t
accl = M.a(:,3);

m = cat(2, t, accl);

csvwrite('data.txt', m);
