
#include"BpnnReaderHelper.h"

BPNNBicycleSetHelper::BPNNBicycleSetHelper() {

}
void BPNNBicycleSetHelper::BPNN_bicycleSet(AroyaReader&reader) {
	//ɾ����ֵ��
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
	//ɾ���Ƿ�����
	reader.deleteInstantZero();
	//����ʱ������
	reader.dispartTime("dteday");
	//������ɢ������
	reader.discrete(reader.findTable("weekday"));
	reader.discrete(reader.findTable("month"));

	//�����������������
	//ʱ����ɢ��
	reader.discrete(reader.findTable("hr"));
	//������ɢ��
	reader.discrete(reader.findTable("weathersit"));

	//ɾ�����ݱ��
	reader.deleteColumn(reader.findTable("instant"));
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