%Recorre todo el dataset y aplica una rotacion aleatoria de entre -ang y and a cada imagen (rotaciones distintas)
l = 42000
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
	dmt = dm';
	v = dmt(:)';
	v = [digit v];
	data = [ data; v];
end
csvwrite("./rotate.csv", data);