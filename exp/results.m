for k = [5 10 15 20 25 30 40 50 60 80 100 150]
	disp("DataSet: 10000, kK-fold:10, kKnn:5 AlphaPca:"+k+" TruePositives/Total(prom):"+precision("./results/results10k5ktrainAlpha"+k+".csv"));
end