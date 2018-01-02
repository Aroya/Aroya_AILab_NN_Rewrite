项目为VS项目
https://github.com/Aroya/Aroya_AILab_NN_Rewrite

main函数在Source.cpp中 默认3层,中间层为20个节点

文件夹lib/中
	Reader负责文件读取
	ReaderHelper和子类BpnnReaderHelper负责对读取的生数据进行离散化、归一化等处理
	Date负责处理时间字符串为月份、日期、星期、节日数据
	Bpnn负责神经网路部分

当在训练集上的平均误差>11000时，不输出测试集结果
	平均误差<11000时，运行测试集，结果输出在out/目录下，文件格式为
	result_CpuClockTicks_MseOnTrainTest.csv
	CpuClockTicks为使用ctime的clock获取的CPU时间，用作随机数，并为生成的文件按时间排序
	MseOnTrainTest为运行测试集时的平均误差

	上交的最好数据为之前在训练集上平均误差为10878.8的结果，因为优化了步长，多次迭代可以得到训练集上平均误差更小的结果，应该会得到更优的结果。