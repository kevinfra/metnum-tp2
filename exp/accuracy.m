function [prom] = accuracy(data)
	p = 0;
	for i = 1:size(data,1)
		tp = 0;
		total = 0;
		for d = 0:9
			tp = tp + data(i, 2 + d*3);
			total = total + data(i, 4 + d*3);
		end
		p = p + tp/total;
	end
	prom = p/size(data,1);
end