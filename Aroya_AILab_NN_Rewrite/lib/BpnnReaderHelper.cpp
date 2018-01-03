
#include"BpnnReaderHelper.h"

BPNNBicycleSetHelper::BPNNBicycleSetHelper() {

}
void BPNNBicycleSetHelper::BPNN_bicycleSet(AroyaReader&reader) {
	//ɾ����ֵ��
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
	//ɾ���Ƿ�����
	reader.deleteInstantZero();
	//����ʱ������
	reader.dispartTime("dteday");
	//������ɢ������
	reader.discrete(reader.findTable("weekday"));
	reader.discrete(reader.findTable("month"));
	reader.discrete(reader.findTable("year"));
	//reader.deleteColumn(reader.findTable("month"));

	//�����������������
	//ʱ����ɢ��
	reader.discrete(reader.findTable("hr"));


	//������ɢ��
	reader.discrete(reader.findTable("weathersit"));

	//ɾ�����ݱ��
	reader.deleteColumn(reader.findTable("instant"));

	//������Ϊ��ɢ
	//reader.PercisionDown(reader.findTable("windspeed"));
	//reader.discrete(reader.findTable("windspeed"));

	//hum��ɢ
	//reader.discrete(reader.findTable("hum"));

	//ɾ��11������
	//reader.deleteRows("year/2011", "1");
}

void BPNNBicycleSetHelper::BPNN_bicycleSetInsert(AroyaReader&reader) {
	//��������reader���뵱ǰhelper
	//string��double
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