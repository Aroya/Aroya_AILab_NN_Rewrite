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
	//�洢ÿһ���W����
	vector<MatrixXd> W;
	//�洢ÿһ��ļ�����
	vector<VectorXd> X_Origin;
	//�洢ÿһ���������
	vector<VectorXd> X;

};
#endif