#ifndef AROYA_BPNN_READER_HELPER
#define AROYA_BPNN_READER_HELPER

#include"Reader.h"
#include"ReaderHelper.h"

class BPNNBicycleSetHelper :public AroyaReaderHelper {
public:
	BPNNBicycleSetHelper();
	//����reader���ݴ���
	void BPNN_bicycleSet(AroyaReader&reader);
	//�����flag����
	void BPNN_bicycleSetInsert(AroyaReader&reader);
	//������flag����
	void BPNN_bicycleSetInsertFlag(AroyaReader&reader);
};

#endif