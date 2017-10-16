function [] = crossval(size, ks, file)
	c = cvpartition(size, 'KFold', ks);
	fid = fopen(file + '.in','wt');
	for k = 1:ks
		t = training(c, k);
		for i = 1:(size - 1)
	    	fprintf(fid,'%d ', t(i));
		end
		fprintf(fid,'%d', t(size));
	    fprintf(fid,'\n');
	end
	fclose(fid)
end