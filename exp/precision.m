function [p] = precision(data, digit)
	p = 0;
	for i = 1:size(data,1)
		tp = data(i, 2 + digit*3);
		fp = data(i, 3 + digit*3);
		p = p + tp/(tp + fp);
	end
	p = p / size(data,1);
end