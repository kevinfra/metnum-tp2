%Recorre todo el dataset y aplica una distorcion aleatoria a cada imagen
l = 42000
data = csvread("./train.csv",1,0,[1,0,l,784]);
for i = 1:l
	if mod(i,100) == 0 
		disp(i);
	end
	m = vec2mat(data(i,2:end), 28);
	digit = data(i,1);
	dm = distortion(m, 6, 100);
	%figure;
	%subplot(122); imagesc(dm); axis image;
	%colormap gray
	dmt = dm';
	v = dmt(:)';
	v = [digit v];
	data = [ data; v];
end
csvwrite("./distortion.csv", data);