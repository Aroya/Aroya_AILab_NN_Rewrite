//#define EIGEN_VECTORIZE_SSE4_2//若不支持AVX2请使用此项
#define EIGEN_VECTORIZE_AVX2//Eigen指令集优化
#include<iostream>
using namespace std;
#include"lib\BPNN2.h"//BPNN中使用到Eigen库
#include"lib\Divider.h"//划分文件
#include"lib\Reader.h"//读取文件
#include"lib\BpnnReaderHelper.h"//处理Reader中的生数据
#include"lib\BPNN_Activation.h"//激活函数
#define Test//每次迭代都测试
			//当大于BPNN2.h中的MinAccurary阈值时
			//不输出
//#define validate
int main() {
#ifdef validate//使用验证集
	//分割文件
	Divider("data/origin.csv");
#endif

	AroyaReader train;
	//train.read("data/train.csv");
	//为了不丢失数据，直接使用原文件
	train.read("data/origin.csv");


	//helper处理数据
	BPNNBicycleSetHelper trainHelper;
	//时间处理、离散化处理、处理?和合计的特殊值
	trainHelper.BPNN_bicycleSet(train);
	//插入处理后的reader到helper
	trainHelper.BPNN_bicycleSetInsert(train);
	//归一化，会先读取文件从文件中读入之前的归一化数据
	//所以第一次运行提示没有文件，之后生成一个
	trainHelper.normalization();
	//写出拥有的table
	trainHelper.saveTable("table.csv");

	//使用helper选取cnt数据
	BPNNBicycleSetHelper trainFlag;
	trainFlag.BPNN_bicycleSetInsertFlag(train);

#ifdef validate//验证集
	AroyaReader vali;
	vali.read("data/validation.csv");
	BPNNBicycleSetHelper valiHelper;
	valiHelper.BPNN_bicycleSet(vali);
	valiHelper.BPNN_bicycleSetInsert(vali);
	//使用训练集的table和其顺序设定当前helper中的列
	valiHelper.transformTable("table.csv");
	valiHelper.normalization();

	BPNNBicycleSetHelper valiFlag;
	valiFlag.BPNN_bicycleSetInsertFlag(vali);
#endif

	AroyaReader test;
	test.read("data/test.csv");
	BPNNBicycleSetHelper testHelper;
	testHelper.BPNN_bicycleSet(test);
	testHelper.BPNN_bicycleSetInsert(test);
	//使用训练集的table和其顺序设定当前helper中的列
	testHelper.transformTable("table.csv");
	testHelper.normalization();

	//设置隐藏层+输出层数量
	int l[] = { 200,100,50,1 };
	int layers = sizeof(l) / sizeof(int) + 1;
	//初始化BPNN总层数
	BPNN bpnn(layers);
	//设置输入节点数
	bpnn.setInputNodes(trainHelper.getColumns());
	//设置输入层之后的每层节点数
	bpnn.setLayerNodes(l);
	//使用helper接口获取bpnn需要的数据结构
	double **db = trainHelper.getDataPointer();
	double **fdb = trainFlag.getDataPointer();
	int dr = trainHelper.getRows();
#ifdef validate
	double **vdb = valiHelper.getDataPointer();
	double **vfdb = valiFlag.getDataPointer();
	int vdr = valiHelper.getRows();
#endif

	double **tdb = testHelper.getDataPointer();
	int tdr = testHelper.getRows();
	
	/*runGroup参数
	void runGroup(double**数据矩阵(数据包), double**期望的输出(CNT数据), const int&数据组数,
	double(*激活函数)(const double&) = 线性, double(*激活函数求导)(const double&) = 线性求导,
	int writeFileTest = 不写文件只训练);
	*/
	for (int i = 0; i < 999999; i++) {
		printf("************%d*************\n",i);
		bpnn.runGroup(db, fdb, dr, softmax, softmaxD);

#ifdef validate
		bpnn.runGroup(vdb, vfdb, vdr, softmax, softmaxD,-1);//-1时不写文件只输出Err
#endif
#ifdef Test
		//output to out/result_CpuClockTicks_MseOnTrainTest.csv
		//writeFileTest为0时运行完结果只输出，不与期望的输出比对
		//也就是不使用这部分数据，可以直接传入nullptr
		bpnn.runGroup(tdb, nullptr, tdr, softmax, softmaxD, 0);
#endif // Test
	}
#ifndef Test//如果没有ifndef将会在迭代完成后再输出文件
	bpnn.runGroup(tdb, nullptr, tdr, softmax, softmaxD, 0);

#endif // !Test Output after all iteration
	system("pause");
}