function [res] = f1(data, digit)
	r = recall(data, digit);
	p = precision(data, digit);
	res = 2 * (r * p) / (r + p);
end