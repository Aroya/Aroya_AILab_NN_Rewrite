#ifndef AROYA_BPNN
#define AROYA_BPNN

#include<vector>
using namespace std;

#include<Eigen/Dense>
using namespace Eigen;

class BPNN_init {
public:
	int *nodes;
	int layers;
	BPNN_init(int*nodes_, const int&layers_);
};

class BPNN {
public:
	BPNN();
	void init(const BPNN_init&bag);
private:
	//存储每一层的W矩阵
	vector<MatrixXd> W;
	//存储每一层的计算结果
	vector<VectorXd> X_Origin;
	//存储每一层的输出结果
	vector<VectorXd> X;

};
#endif