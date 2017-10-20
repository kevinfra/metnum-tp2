function [new] = distortion(img, sig, alpha)
	switch nargin
	    case 1
			sig=4; 
			alpha=60;
	    case 2
			alpha=60;
	end

	%Genera un desplazamiento aleatorio pero acotado
	dx = -1+2*rand(size(img)); 
	dy = -1+2*rand(size(img)); 

	%Suaviza con un filtro gausseano
	fdx=imgaussfilt(dx, sig);
	fdy=imgaussfilt(dy, sig);
	%Normalizar
	n=sum((fdx(:).^2+fdy(:).^2)); 
	fdx=alpha*fdx./n;
	fdy=alpha*fdy./n;
	
	[y x]=ndgrid(1:size(img,1),1:size(img,2));
	%Aplica el desplazamiento aleatorio usando la interpolacion de griddata
	new = griddata(x-fdx,y-fdy,double(img),x,y);
	new(isnan(new))=0;
	
end
