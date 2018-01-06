#include"BPNN2.h"

static stringstream sst;
static string outputFileName;
static string sstOut;
static string sstOut2;
double defaultActive(const double&t) { return t; }
double defaultActiveD(const double&t) { return 1.0; }
double BPNN::dynamic() {
	//2隐藏层
	return 0.0001;
	//3隐藏层
	//return 0.00001;
	//return 0.0005;
	//if(loss>20000) return 0.0001;
	//else if (loss>13000) return 0.00005;
	//else if (loss>9000) return 0.00001;
	//else if (loss > 7000) return 0.000005;
	//else return 0.000001;
	//多层神经网路
	//if(loss>20000) return 0.00001;
	//else if (loss>10000) return 0.000005;
	//else return 0.000001;
	//sigmoid 
	//多层神经网路
	if (loss>20000) return 0.0005;
	//else if (loss>10000) return 0.0001;
	else return 0.0001;
}
BPNN_init::BPNN_init(int*nodes_, const int&layers_) {
	nodes = nodes_;
	layers = layers_;
}
BPNN::BPNN(const int&CountOfLayers) {
	layers = CountOfLayers;
	layerNodes = new int[CountOfLayers];
}

void BPNN::setInputNodes(const int&Nodes) {
	layerNodes[0] = Nodes;
	W.push_back(emptyMatrix);
	X_Origin.push_back(emptyVector);
	X.push_back(emptyVector);
	X[0].resize(Nodes);
	X[0].setZero();
	Bias.push_back(emptyVector);

	fixY.push_back(emptyVector);
	fixBias.push_back(emptyVector);
	diffBias.push_back(emptyVector);
	Diff.push_back(emptyVector);
	fixW.push_back(emptyMatrix);
}
//copy input data to first index of private data
void BPNN::setInputData(double* NodeDataArray, double(*active)(const double&)) {
	int i, j = layerNodes[0];
	for (i = 0; i < j; i++) {
		X[0](i) = NodeDataArray[i];
	}
}
//set layer array size(not contain input)
void BPNN::setLayerNodes(int* Nodes) {
	int i, j, k;
	for (i = 1, j = 0; i < layers; i++, j++) {
		k = Nodes[j];
		layerNodes[i] = k;

		X_Origin.push_back(emptyVector);
		X_Origin[i].resize(k);
		X_Origin[i].setZero();

		X.push_back(emptyVector);
		X[i].resize(k);
		X[i].setZero();
		W.push_back(emptyMatrix);
		//一行为一个节点的W
		//列数为上一层的节点数
		W[i].resize(k, layerNodes[j]);
		//W[i].setZero();
		W[i].setRandom();

		//Bias
		Bias.push_back(emptyVector);
		Bias[i].resize(k);
		//Bias[i].setZero();
		Bias[i].setRandom();

		fixY.push_back(emptyVector);
		fixY[i].resize(k);
		fixY[i].setZero();
		fixBias.push_back(emptyVector);
		fixBias[i].resize(k);
		fixBias[i].setZero();
		diffBias.push_back(emptyVector);
		diffBias[i].resize(k);
		diffBias[i].setZero();
		Diff.push_back(emptyVector);
		Diff[i].resize(k);
		Diff[i].setZero();
		fixW.push_back(emptyMatrix);
		fixW[i].resize(k, layerNodes[j]);
		fixW[i].setZero();
	}
}
//Get Ans
void BPNN::updateLayers(double(*active)(const double&)) {
	int k, l;
	for (int i = 1, j = 0; i < layers; i++, j++) {
//#ifdef ShowAllNodes
//		cout << "X[" << j << "]:\n";
//		cout << X[j] << endl;
//		cout << "W[" << i << "]:\n";
//		cout << W[i] << endl;
//#endif // ShowAllNodes


		//h=WX
		X_Origin[i] = W[i] * X[j] + Bias[i];

		//激活
		l = layerNodes[i];
#ifndef LastLayerLinear
		for (k = 0; k < l; k++) {
			X[i](k) = active(X_Origin[i](k));
		}
#endif
#ifdef LastLayerLinear
		if (i == layers - 1) {
			X[i] = X_Origin[i];
		}
		else for (k = 0; k < l; k++) {
			X[i](k) = active(X_Origin[i](k));
		}
#endif

	}
}
//Update W and bias
void BPNN::updateParameter(double(*activeD)(const double&)) {
	int i, j, k, l;
	for (i = layers - 1, j = layers - 2; i > 0; i--, j--) {
		l = layerNodes[i];
		for (k = 0; k < l; k++) {
#ifdef LastLayerLinear
			if (i == layers - 1) {
				Diff[i](k) = 1;
			}
			else {
				Diff[i](k) = activeD(X_Origin[i](k));
				
			}
#endif
#ifndef LastLayerLinear
			Diff[i](k) = activeD(X_Origin[i](k));
#endif
			diffBias[i](k) = fixY[i](k)*Diff[i](k);
		}
		//cout << "layers:\t\t" << i << endl;
		//fixBias[i] += diffBias[i];
		//cout << "DiffBias\n";
		//cout << diffBias[i] << endl;
		//cout << "X.trans\n";
		//cout << X[j].transpose() << endl;
		//system("pause");
		fixBias[i] += diffBias[i];
		fixW[i] += diffBias[i] * X[j].transpose();
		fixY[j] = W[i].transpose()*diffBias[i];
	}
}
//input expect value(output node)
void BPNN::setExpectData(double*Data, double(*active)(const double&)) {
	VectorXd temp;
	int last = layers - 1;
	int size = layerNodes[last];
	temp.resize(size);
	for (int i = 0; i < size; i++) {
		fixY[last](i) = Data[i] - X[last](i);
	}
	
	//sigmoid
	//fixY[last] = temp - X_Origin[last];
}
void BPNN::learn(const int&groups) {
	int i;
	for (i = layers - 1; i > 0; i--) {
		Bias[i] = Bias[i] + dynamic()*fixBias[i] / groups;
		W[i] = W[i] + dynamic()*fixW[i] / groups;
	}
}
void BPNN::clearFix() {
	for (int i = 0; i < layers; i++) {
		fixW[i].setZero();
		fixBias[i].setZero();
	}
}
//run with group data
void BPNN::runGroup(double**group, double**flag, const int&groups,
	double(*active)(const double&), double(*activeD)(const double&),
	int writeFile) {
	if (writeFile) {
		clearFix();
		loss = 0;
		//forward = 0;
		for (int i = 0; i < groups; i++) {
			setInputData(group[i], active);
			updateLayers(active);
			setExpectData(flag[i], active);
			
			//if (i == 2)system("pause");
			//cout << "******************\n" << fixY[2] << endl;
			if (writeFile > 0)updateParameter(activeD);
			int lastLayer = layers - 1;
			for (int j = 0; j < layerNodes[lastLayer]; j++) {
				//forward += flag[i][j] - layerData[layers - 1][j];
				loss += pow(fixY[lastLayer](j), 2);
			}
		}
		if (writeFile > 0) {//>0训练
			cout << "Loss:\t\t" << (loss /= double(groups)) << endl;
			learn(groups);
		}
		else {//<0验证
			cout << "ValiLoss:\t" << (loss /= double(groups)) << endl;
		}
	}
	else {//==0测试
		sst.str("");
		sst.clear();
		sst << loss;
		sst >> sstOut2;
		if (loss>MinAccurary) {
			cout << "Test error:loss too high:\t" << loss << endl;
			return;
		}
		if (sstOut2 == "nan" || sstOut2 == "-nan(ind)") {
			cout << "Error:\t" << loss << endl;
			system("pause");
			exit(0);
		}

		outputFileName = "out/result_";
		sst.str("");
		sst.clear();
		sst << clock();
		sst >> sstOut;

		outputFileName = outputFileName + sstOut + "_" + sstOut2 + ".csv";

		ofstream fout;
		fout.open(outputFileName);

		for (int i = 0; i < groups; i++) {
			setInputData(group[i], active);
			updateLayers(active);
			for (int i = 0; i < layerNodes[layers - 1]; i++) {
				//fout << int(activation[layers - 1][i]) << endl;
				fout << max(int(X[layers - 1](i)),0) << endl;
				//fout << X[layers - 1](i) << endl;
			}
		}
		fout.close();
	}
#ifdef ShowAllNodes
	for (int i = 0; i < layers; i++) {
		cout << "*************************************\n";
		cout << "Layer\t\t" << i << endl;
		cout << "X_Origin\t" << endl;
		cout << X_Origin[i] << endl;
		cout << "Diff\t\t" << endl;
		cout << Diff[i] << endl;
		cout << "X\t\t" << endl;
		cout << X[i] << endl;
		cout << "fixY\t\t" << endl;
		cout << fixY[i] << endl;
		cout << "fixBias\t\t" << endl;
		cout << fixBias[i] << endl;
		cout << "Bias\t\t" << endl;
		cout << Bias[i] << endl;
		cout << "fixW\t\t" << endl;
		cout << fixW[i] << endl;
		cout << "W\t" << endl;
		cout << W[i] << endl;
		cout << "*************************************\n";
	}
	system("pause");
#endif // ShowAllNodes

}

