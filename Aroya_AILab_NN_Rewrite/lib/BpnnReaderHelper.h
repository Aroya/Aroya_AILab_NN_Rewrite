#ifndef AROYA_BPNN_READER_HELPER
#define AROYA_BPNN_READER_HELPER


class BPNNBicycleSetHelper :public AroyaReaderHelper {
public:
	BPNNBicycleSetHelper();
	void BPNN_bicycleSet(AroyaReader&reader);
};

#endif