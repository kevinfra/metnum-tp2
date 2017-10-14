l = 42000
%l = 20 
ang = 30
data = csvread("./train.csv",1,0,[1,0,l,784]);
for i = 1:l
	if mod(i,100) == 0 
		disp(i);
	end
	m = vec2mat(data(i,2:end), 28);
	digit = data(i,1);
	rot = -ang + (ang+ang)*rand(10,1);
	dm = imrotate(m, rot(1,1), 'bilinear', 'crop');
	%figure;
	%subplot(122); imagesc(dm); axis image;
	%colormap gray
	dmt = dm';
	v = dmt(:)';
	v = [digit v];
	data = [ data; v];
end
csvwrite("./rotate.csv", data);