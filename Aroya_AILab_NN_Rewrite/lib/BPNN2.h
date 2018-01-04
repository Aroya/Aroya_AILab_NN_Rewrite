#ifndef AROYA_BPNN
#define AROYA_BPNN

#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>
#include<ctime>
using namespace std;

#include<Eigen/Dense>
using namespace Eigen;
//#define ShowAllNodes

double defaultActive(const double&t);
double defaultActiveD(const double&t);


class BPNN_init {
public:
	int *nodes;
	int layers;
	BPNN_init(int*nodes_, const int&layers_);
};

class BPNN {
public:
	//contain input,hidden and output
	BPNN(const int&CountOfLayers);
	//set input array size
	void setInputNodes(const int&Nodes);
	//copy input data to first index of private data
	void setInputData(double* NodeDataArray, double(*)(const double&));
	//set layer array size(not contain input)
	void setLayerNodes(int* Nodes);
	//Get Ans
	void updateLayers(double(*)(const double&) = defaultActive);
	//Update W and bias
	void updateParameter(double(*)(const double&) = defaultActiveD);
	//input expect value(output node)
	void setExpectData(double*Data, double(*)(const double&));
	//run with group data
	void runGroup(double**groupData, double**flag, const int&groups,
		double(*)(const double&) = defaultActive, double(*)(const double&) = defaultActiveD,
		int writeFileTest = 1);
private:
	//�洢ÿһ���W����
	vector<MatrixXd> W;
	//�洢ÿһ��ļ�����
	vector<VectorXd> X_Origin;
	//�洢ÿһ���������
	vector<VectorXd> X;
	//�洢ÿһ���Bias
	vector<VectorXd> Bias;
	//ÿ���ƫ��
	vector<VectorXd> fixY;
	//ÿ���Biasƫ��
	vector<VectorXd> fixBias;
	//ÿ���Biasƫ�ƣ�����������
	vector<VectorXd> diffBias;
	//ÿ��ļ���ֵ��
	vector<VectorXd> Diff;
	//ÿ���Wƫ��ֵ
	vector<MatrixXd> fixW;

	MatrixXd emptyMatrix;
	VectorXd emptyVector;
	int layers;
	int *layerNodes;

	double loss;
	double dynamic();
	void learn(const int&groups);
	void clearFix();
};
#endif