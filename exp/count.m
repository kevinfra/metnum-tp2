%l = 84000
l = 42000
data = csvread("./train.csv",1,0,[1,0,l,1]);
n = zeros(1, 10);
for i = 1:l
	if mod(i,100) == 0 
		disp(i);
	end
	digit = data(i,1);
	n(digit + 1) = n(digit + 1) + 1;
end
csvwrite("./rotate.csv", data);