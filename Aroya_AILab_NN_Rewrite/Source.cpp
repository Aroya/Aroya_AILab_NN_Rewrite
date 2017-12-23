#include<iostream>
#include"lib\Reader.h"
#include"lib\BpnnReaderHelper.h"
using namespace std;

int main() {
	AroyaReader train;
	//train.read("examples/test0.csv");
	train.read("data/train.csv");
	
	//helper处理数据


	BPNNBicycleSetHelper trainHelper;
	trainHelper.BPNN_bicycleSet(train);
	trainHelper.BPNN_bicycleSetInsert(train);
	trainHelper.normalization();
	trainHelper.writeFile("test0_out.csv");

	BPNNBicycleSetHelper trainFlag;
	trainFlag.BPNN_bicycleSetInsertFlag(train);
	trainFlag.writeFile("test0_out_flag.csv");


	system("pause");
}