#include<iostream>
#include"lib\Reader.h"
using namespace std;

int main() {
	AroyaReader train;
	train.read("train.csv");
	//因为已经存在
	train.deleteTable(train.findTable("dteday"));
	

	system("pause");
}