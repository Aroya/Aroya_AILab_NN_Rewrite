#ifndef AROYA_BPNN_READER_HELPER
#define AROYA_BPNN_READER_HELPER

#include"Reader.h"
#include"ReaderHelper.h"

class BPNNBicycleSetHelper :public AroyaReaderHelper {
public:
	BPNNBicycleSetHelper();
	//仅做reader数据处理
	void BPNN_bicycleSet(AroyaReader&reader);
	//插入非flag数据
	void BPNN_bicycleSetInsert(AroyaReader&reader);
	//仅插入flag数据
	void BPNN_bicycleSetInsertFlag(AroyaReader&reader);
};

#endif