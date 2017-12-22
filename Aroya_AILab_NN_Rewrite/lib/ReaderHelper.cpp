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

void AroyaReaderHelper::insert(AroyaReader&reader, const int&col) {
	//table����
	table.push_back(reader.getStringData(0, col));
	int i, l = reader.getRows(), j = buffer.size();
	//���д���
	buffer.push_back(empty);
	for (i = 1; i < l; i++) {
		buffer[j].push_back(reader.getDoubleData(i, col));
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
	int i, j, k, l;
	double max, min, t;
	bool exist;
	//��һ��
	vector<string>normal_table;
	vector<double>normal_max;
	vector<double>normal_min;
	//���й�һ���ļ���¼����ж�ȡ��׼
	ifstream fin;
	fin.open("normal.csv");
	if (fin.is_open()) {
		fin.close();
		AroyaReader normal_reader;
		normal_reader.read("normal.csv");
		j = normal_reader.getColumns();
		for (i = 0; i < j; i++) {
			normal_table.push_back(normal_reader.getStringData(0, i));
			normal_max.push_back(normal_reader.getDoubleData(1, i));
			normal_min.push_back(normal_reader.getDoubleData(2, i));
		}
	}

	//û����������׼
	j = table.size();
	for (i = 0; i < j; i++) {
		//�ٵ�ǰtable�в���
		l = normal_table.size();
		exist = false;
		for (k = 0; k < l; k++) {
			if (table[i] == normal_table[k]) {
				exist = true;
				break;
			}
		}
		//������
		if (!exist) {
			normal_table.push_back(table[i]);
			//�������ڹ�һ���ı�׼
			l = buffer[i].size();
			max = buffer[i][0];
			min = buffer[i][0];
			//�ҵ����ֵ����Сֵ
			for (k = 0; k < l; k++) {
				t = buffer[i][k];
				if (t > max) {
					max = t;
				}
				else if (t < min) {
					min = t;
				}
			}
			normal_max.push_back(max);
			normal_min.push_back(min);
		}
	}

	//��һ������


	//��¼�ļ�
}