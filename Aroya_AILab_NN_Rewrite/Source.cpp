#include<iostream>
#include"lib\Reader.h"
#include"lib\ReaderHelper.h"
using namespace std;

int main() {
	AroyaReader train;
	train.read("train.csv");
	
	//helper��������
	BPNNBicycleSetHelper trainHelper;
	trainHelper.BPNN_bicycleSet(train);
	

	system("pause");
}