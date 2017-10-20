function [p] = recall(data, digit)
	p = 0;
	for i = 1:size(data,1)
		tp = data(i, 2 + digit*3);
		total = data(i, 4 + digit*3);
		p = p + tp/total;
	end
	p = p / size(data,1);
end