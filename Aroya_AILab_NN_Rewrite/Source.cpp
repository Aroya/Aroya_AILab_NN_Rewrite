#include<iostream>
using namespace std;
#include"lib\BPNN2.h"
#include"lib\Divider.h"
#include"lib\Reader.h"
#include"lib\BpnnReaderHelper.h"
#include"lib\BPNN_Activation.h"
#define Test
//#define validate
int main() {
	//Divider("data/origin.csv");

	AroyaReader train;
	//train.read("examples/xor.csv");
	//train.read("data/train.csv");
	train.read("data/origin.csv");


	//helper处理数据
	BPNNBicycleSetHelper trainHelper;
	trainHelper.BPNN_bicycleSet(train);
	trainHelper.BPNN_bicycleSetInsert(train);
	trainHelper.normalization();
	trainHelper.saveTable("table.csv");
	//trainHelper.BPNN_bicycleSetInsertFlag(train);
	//trainHelper.writeFile("test0_out_train.csv");

	//system("pause");

	BPNNBicycleSetHelper trainFlag;
	trainFlag.BPNN_bicycleSetInsertFlag(train);
	//trainFlag.writeFile("test0_out_flag.csv");

#ifdef validate
	AroyaReader vali;
	vali.read("data/validation.csv");
	BPNNBicycleSetHelper valiHelper;
	valiHelper.BPNN_bicycleSet(vali);
	valiHelper.BPNN_bicycleSetInsert(vali);
	valiHelper.transformTable("table.csv");
	valiHelper.normalization();

	BPNNBicycleSetHelper valiFlag;
	valiFlag.BPNN_bicycleSetInsertFlag(vali);
#endif
#ifdef Test
	AroyaReader test;
	test.read("data/test.csv");
	BPNNBicycleSetHelper testHelper;
	testHelper.BPNN_bicycleSet(test);
	testHelper.BPNN_bicycleSetInsert(test);
	testHelper.transformTable("table.csv");
	testHelper.normalization();
	//testHelper.BPNN_bicycleSetInsertFlag(test);
	//testHelper.writeFile("test0_out_test.csv");
#endif // Test

	int layers = 5;
	BPNN bpnn(layers);
	bpnn.setInputNodes(trainHelper.getColumns());
	int l[4] = { 600,400,200,1 };
	bpnn.setLayerNodes(l);
	double **db = trainHelper.getDataPointer();
	double **fdb = trainFlag.getDataPointer();
	int dr = trainHelper.getRows();
#ifdef validate
	double **vdb = valiHelper.getDataPointer();
	double **vfdb = valiFlag.getDataPointer();
	int vdr = valiHelper.getRows();
#endif

#ifdef Test
	double **tdb = testHelper.getDataPointer();
	int tdr = testHelper.getRows();
#endif // Test

	for (int i = 0; i < 999999; i++) {
		cout << i << "\t\t";
		bpnn.runGroup(db, fdb, dr, softmax, softmaxD);
		//bpnn.runGroup(db, nullptr, dr, softmax, softmaxD, 0);
		//bpnn.runGroup(db, fdb, dr, sigmoid, sigmoidD);
		//bpnn.runGroup(db, fdb, dr, sigmoid, sigmoidD,0);
		//bpnn.runGroup(db, fdb, dr);
		//bpnn.runGroup(db, fdb, dr, defaultActive, defaultActiveD, 0);
#ifdef validate
		bpnn.runGroup(vdb, vfdb, vdr, softmax, softmaxD,-1);
#endif
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