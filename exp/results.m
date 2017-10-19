for k = [1 2 3 4 5 7 8 9 10 15 20 30]
	disp("DataSet: 10000, kK-fold:10, kKnn:"+ k + " AlphaPca:15 TruePositives/Total(prom):"+precision("./results/k/results10k"+k+"ktrainAlpha15.csv"));
end

for k = [1 2 3 4 5 7 8 9 10 15 20 30]
	disp("DataSet: 10000, kK-fold:10, kKnn:"+ k + " AlphaPca:30 TruePositives/Total(prom):"+precision("./results/k/results10k"+k+"ktrainAlpha30.csv"));
end
