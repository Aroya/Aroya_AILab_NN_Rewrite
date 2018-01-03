
#include"BpnnReaderHelper.h"

BPNNBicycleSetHelper::BPNNBicycleSetHelper() {

}
void BPNNBicycleSetHelper::BPNN_bicycleSet(AroyaReader&reader) {
	//删除空值行
	int i, j, k = reader.getColumns() - 1;
	for (i = 0; i < reader.getRows(); i++) {
		for (j = 0; j < k; j++) {
			if (reader.getStringData(i, j) == "?") {
				reader.deleteRow(i);
				i--;
				break;
			}
		}
	}
	//删除非法数据
	reader.deleteInstantZero();
	//处理时间数据
	reader.dispartTime("dteday");
	//处理离散的数据
	reader.discrete(reader.findTable("weekday"));
	reader.discrete(reader.findTable("month"));
	reader.discrete(reader.findTable("year"));
	//reader.deleteColumn(reader.findTable("month"));

	//处理非数字类型数据
	//时间离散化
	reader.discrete(reader.findTable("hr"));


	//天气离散化
	reader.discrete(reader.findTable("weathersit"));

	//删除数据编号
	reader.deleteColumn(reader.findTable("instant"));

	//连续降为离散
	//reader.PercisionDown(reader.findTable("windspeed"));
	//reader.discrete(reader.findTable("windspeed"));

	//hum离散
	//reader.discrete(reader.findTable("hum"));

	//删除11年数据
	//reader.deleteRows("year/2011", "1");
}

void BPNNBicycleSetHelper::BPNN_bicycleSetInsert(AroyaReader&reader) {
	//将处理后的reader插入当前helper
	//string→double
	int i, j;
	j = reader.getColumns();
	for (i = 0; i < j; i++) {
		if (reader.getStringData(0, i) != "cnt")
			insert(reader, i);
	}
}

void BPNNBicycleSetHelper::BPNN_bicycleSetInsertFlag(AroyaReader&reader) {
	int ps = reader.findTable("cnt");
	insert(reader, ps);
}