#include<iostream>
#include"lib\Reader.h"
#include"lib\BpnnReaderHelper.h"
#include"lib\date.h"
using namespace std;

int main() {
	AroyaReader train;
	train.read("examples/test0.csv");
	
	//helper处理数据
	BPNNBicycleSetHelper trainHelper;
	trainHelper.BPNN_bicycleSet(train);
	trainHelper.normalization();
	trainHelper.writeFile("test0_out.csv");
	

	system("pause");
}