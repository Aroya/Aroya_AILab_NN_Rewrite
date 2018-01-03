#include<iostream>
using namespace std;
#include"lib\BPNN.h"
#include"lib\Divider.h"
#include"lib\Reader.h"
#include"lib\BpnnReaderHelper.h"
#include"lib\BPNN_Activation.h"
#define Test
int main() {
	//Divider("data/train.csv");

	AroyaReader train;
	//train.read("examples/test0.csv");
	train.read("data/train.csv");


	//helper处理数据
	BPNNBicycleSetHelper trainHelper;
	trainHelper.BPNN_bicycleSet(train);
	trainHelper.BPNN_bicycleSetInsert(train);
	trainHelper.normalization();
	trainHelper.saveTable("table.csv");
	//trainHelper.writeFile("test0_out_train.csv");

	//system("pause");

	BPNNBicycleSetHelper trainFlag;
	trainFlag.BPNN_bicycleSetInsertFlag(train);
	//trainFlag.writeFile("test0_out_flag.csv");

#ifdef Test
	AroyaReader test;
	test.read("data/test.csv");
	BPNNBicycleSetHelper testHelper;
	testHelper.BPNN_bicycleSet(test);
	testHelper.BPNN_bicycleSetInsert(test);
	//testHelper.writeFile("test0_out_test2.csv");
	testHelper.transformTable("table.csv");
	testHelper.normalization();
	//testHelper.writeFile("test0_out_test.csv");
#endif // Test

	int layers = 3;
	BPNN bpnn(layers);
	bpnn.setInputNodes(trainHelper.getColumns());
	int l[2] = { 30,1 };
	bpnn.setLayerNodes(l);
	double **db = trainHelper.getDataPointer();
	double **fdb = trainFlag.getDataPointer();
	int dr = trainHelper.getRows();

#ifdef Test
	double **tdb = testHelper.getDataPointer();
	int tdr = testHelper.getRows();
#endif // Test

	for (int i = 0; i < 999999; i++) {
		bpnn.runGroup(db, fdb, dr, softmax, softmaxD);

#ifdef Test
		//output to out/result_CpuClockTicks_MseOnTrainTest.csv
		bpnn.runGroup(tdb, nullptr, tdr, softmax, softmaxD, 0);
#endif // Test


	}
#ifndef Test
	bpnn.runGroup(db, nullptr, dr, softmax, softmaxD, 0);
#endif // !Test

	//for (int i = 0; i < 100; i++)
	//bpnn.runGroup(db, fdb, dr, sigmoid, sigmoidD);

	//bpnn.runGroup(db, nullptr, dr, sigmoid, sigmoidD, 0);

	system("pause");
}