function [new] = distortion(img, sig, alpha)
	switch nargin
	    case 1
			sig=4; 
			alpha=60;
	    case 2
			alpha=60;
	end

	%https://stackoverflow.com/questions/39308301/expand-mnist-elastic-deformations-matlab
	%Compute a random displacement field dx~U(-1,1), dy~U(-1,1)
	dx = -1+2*rand(size(img)); 
	dy = -1+2*rand(size(img)); 

	%Smoothing and normalizing the field:

	%H=fspecial('gauss',[28 28], sig);
	%fdx=imfilter(dx,H);
	%fdy=imfilter(dy,H);
	fdx=imgaussfilt(dx, sig);
	fdy=imgaussfilt(dy, sig);
	n=sum((fdx(:).^2+fdy(:).^2)); %// norm (?) not quite sure about this "norm"
	fdx=alpha*fdx./n;
	fdy=alpha*fdy./n;
	
	[y x]=ndgrid(1:size(img,1),1:size(img,2));
	%The final stage - applying the displacement to the actual pixels using griddata interpolation:
	new = griddata(x-fdx,y-fdy,double(img),x,y);
	new(isnan(new))=0;
	
	%The resulting digit:
	%figure;
	%subplot(121); imagesc(img); axis image;
	%subplot(122); imagesc(new); axis image;
	%colormap gray
end
