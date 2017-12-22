
#include"BpnnReaderHelper.h"

BPNNBicycleSetHelper::BPNNBicycleSetHelper() {

}
void BPNNBicycleSetHelper::BPNN_bicycleSet(AroyaReader&reader) {
	//删除空值行
	int i, j;
	for (i = 0; i < reader.getRows(); i++) {
		for (j = 0; j < reader.getColumns(); j++) {
			if (reader.getStringData(i, j) == "?") {
				reader.deleteRow(i);
				i--;
				break;
			}
		}
	}
	//处理时间数据
	reader.dispartTime("dteday");

	//处理非数字类型数据
	//时间离散化
	reader.discrete(reader.findTable("hr"));
	//天气离散化
	reader.discrete(reader.findTable("weathersit"));

	//删除数据编号
	reader.deleteColumn(reader.findTable("instant"));

	//将处理后的reader插入当前helper
	//string→double
	j = reader.getColumns();
	for (i = 0; i < j; i++) {
		insert(reader, i);
	}

	//调用helper的归一化函数
	//归一化函数未完成

}