#include"ReaderHelper.h"

AroyaReaderHelper::AroyaReaderHelper() {
	//nothing to do yet
}

//insert table
void AroyaReaderHelper::insert(AroyaReader&reader, const char*tableName, const char*myTableName) {
	if (myTableName == nullptr)myTableName = tableName;
	int t = reader.findTable(tableName);	//find table index
	int length = reader.getRows();			//get data size
	int myPosition = findTable(myTableName);//find myTableName index

	if (myPosition < 0) {					//not found create new table
		myPosition = buffer.size();			//point to end of buffer
		buffer.push_back(empty);			//new buffer
		table.push_back(myTableName);		//new table
	}

	for (int i = 1; i < length; i++) {		//push to buffer
		buffer[myPosition].push_back(reader.getDoubleData(i, t));
	}
}
int AroyaReaderHelper::findTable(const char*tableName) {
	int i, j;
	i = table.size();
	for (j = 0; j < i; j++) {
		if (table[j] == tableName)return j;
	}
	return -1;
}

vector<vector<double>> AroyaReaderHelper::getData() {
	vector<vector<double>>temp;
	vector<double>item;
	int i, j, rows, columns;
	rows = buffer[0].size();
	columns = buffer.size();
	for (i = 0; i < rows; i++) {
		item.clear();
		for (j = 0; j < columns; j++) {
			item.push_back(buffer[j][i]);
		}
		temp.push_back(item);
	}
	return temp;
}
void AroyaReaderHelper::normalization() {
	//��һ��
	//���й�һ���ļ���¼����ж�ȡ��׼

	//û����������׼

	//��¼�ļ�
}

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
	//����ʱ������
	reader.dispartTime("dteday");

	//�����������������
	

	//����ʾ���͵���������ת��ɢ


	//��������reader���뵱ǰhelper
	//string��double


	//����helper�Ĺ�һ������
	//��һ������δ���

}