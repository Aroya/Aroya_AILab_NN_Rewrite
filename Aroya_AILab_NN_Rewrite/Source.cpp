//#define EIGEN_VECTORIZE_SSE4_2//����֧��AVX2��ʹ�ô���
#define EIGEN_VECTORIZE_AVX2//Eigenָ��Ż�
#include<iostream>
using namespace std;
#include"lib\BPNN2.h"//BPNN��ʹ�õ�Eigen��
#include"lib\Divider.h"//�����ļ�
#include"lib\Reader.h"//��ȡ�ļ�
#include"lib\BpnnReaderHelper.h"//����Reader�е�������
#include"lib\BPNN_Activation.h"//�����
#define Test//ÿ�ε���������
			//������BPNN2.h�е�MinAccurary��ֵʱ
			//�����
//#define validate
int main() {
#ifdef validate//ʹ����֤��
	//�ָ��ļ�
	Divider("data/origin.csv");
#endif

	AroyaReader train;
	//train.read("data/train.csv");
	//Ϊ�˲���ʧ���ݣ�ֱ��ʹ��ԭ�ļ�
	train.read("data/origin.csv");


	//helper��������
	BPNNBicycleSetHelper trainHelper;
	//ʱ�䴦����ɢ����������?�ͺϼƵ�����ֵ
	trainHelper.BPNN_bicycleSet(train);
	//���봦����reader��helper
	trainHelper.BPNN_bicycleSetInsert(train);
	//��һ�������ȶ�ȡ�ļ����ļ��ж���֮ǰ�Ĺ�һ������
	//���Ե�һ��������ʾû���ļ���֮������һ��
	trainHelper.normalization();
	//д��ӵ�е�table
	trainHelper.saveTable("table.csv");

	//ʹ��helperѡȡcnt����
	BPNNBicycleSetHelper trainFlag;
	trainFlag.BPNN_bicycleSetInsertFlag(train);

#ifdef validate//��֤��
	AroyaReader vali;
	vali.read("data/validation.csv");
	BPNNBicycleSetHelper valiHelper;
	valiHelper.BPNN_bicycleSet(vali);
	valiHelper.BPNN_bicycleSetInsert(vali);
	//ʹ��ѵ������table����˳���趨��ǰhelper�е���
	valiHelper.transformTable("table.csv");
	valiHelper.normalization();

	BPNNBicycleSetHelper valiFlag;
	valiFlag.BPNN_bicycleSetInsertFlag(vali);
#endif

	AroyaReader test;
	test.read("data/test.csv");
	BPNNBicycleSetHelper testHelper;
	testHelper.BPNN_bicycleSet(test);
	testHelper.BPNN_bicycleSetInsert(test);
	//ʹ��ѵ������table����˳���趨��ǰhelper�е���
	testHelper.transformTable("table.csv");
	testHelper.normalization();

	//�������ز�+���������
	int l[] = { 200,100,50,1 };
	int layers = sizeof(l) / sizeof(int) + 1;
	//��ʼ��BPNN�ܲ���
	BPNN bpnn(layers);
	//��������ڵ���
	bpnn.setInputNodes(trainHelper.getColumns());
	//���������֮���ÿ��ڵ���
	bpnn.setLayerNodes(l);
	//ʹ��helper�ӿڻ�ȡbpnn��Ҫ�����ݽṹ
	double **db = trainHelper.getDataPointer();
	double **fdb = trainFlag.getDataPointer();
	int dr = trainHelper.getRows();
#ifdef validate
	double **vdb = valiHelper.getDataPointer();
	double **vfdb = valiFlag.getDataPointer();
	int vdr = valiHelper.getRows();
#endif

	double **tdb = testHelper.getDataPointer();
	int tdr = testHelper.getRows();
	
	/*runGroup����
	void runGroup(double**���ݾ���(���ݰ�), double**���������(CNT����), const int&��������,
	double(*�����)(const double&) = ����, double(*�������)(const double&) = ������,
	int writeFileTest = ��д�ļ�ֻѵ��);
	*/
	for (int i = 0; i < 999999; i++) {
		printf("************%d*************\n",i);
		bpnn.runGroup(db, fdb, dr, softmax, softmaxD);

#ifdef validate
		bpnn.runGroup(vdb, vfdb, vdr, softmax, softmaxD,-1);//-1ʱ��д�ļ�ֻ���Err
#endif
#ifdef Test
		//output to out/result_CpuClockTicks_MseOnTrainTest.csv
		//writeFileTestΪ0ʱ��������ֻ�������������������ȶ�
		//Ҳ���ǲ�ʹ���ⲿ�����ݣ�����ֱ�Ӵ���nullptr
		bpnn.runGroup(tdb, nullptr, tdr, softmax, softmaxD, 0);
#endif // Test
	}
#ifndef Test//���û��ifndef�����ڵ�����ɺ�������ļ�
	bpnn.runGroup(tdb, nullptr, tdr, softmax, softmaxD, 0);

#endif // !Test Output after all iteration
	system("pause");
}