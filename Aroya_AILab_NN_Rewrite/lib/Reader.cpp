#include"Reader.h"
#include"Date.h"

//�����ݲ��������֡�С�������ж�
bool static NotPureNumber(const string&);
bool static PureNumber(const char&);

AroyaReader::AroyaReader() {
	//nothing to do yet
}

void AroyaReader::read(const char*fileName) {
	ifstream fin;
	fin.open(fileName);
	if (!fin.is_open()) {
		cout << "AroyaReader:read() cannot open file!\n";
		system("pause");
	}
	char reading;
	string buffer;
	bool didntInit = true;
	vector<string>emptyVector;
	int nowPoint = 0;
	while (fin.good() && (reading = fin.get()) != -1) {
		//���ݽ��� ��������
		if (reading == ','|| reading == '\n') {
			if (didntInit) {					//init this row
				data.push_back(emptyVector);
				didntInit = false;
			}
			data[nowPoint].push_back(buffer);	//put data to this row

			buffer.clear();						//clear buffer
			if (reading == '\n') {				//next row
				nowPoint++;	
				didntInit = true;
			}
		}
		//�޷ָ��� ��¼����
		else {
			buffer.push_back(reading);
		}
	}
	fin.close();
	rows = data.size();
	columns = data[0].size();
}

string AroyaReader::getStringData(const int&rows, const int&columns) {
	return data[rows][columns];
}

double AroyaReader::getDoubleData(const int&rows, const int&columns) {
	internalSst.str("");
	internalSst.clear();
	internalSst << data[rows][columns];
	double temp;
	internalSst >> temp;
	return temp;
}

int AroyaReader::findTable(const char*tableName) {
	int tables = data[0].size();
	for (int i = 0; i < tables; i++) {
		if (data[0][i] == tableName)return i;
	}
	return -1;
}
int AroyaReader::getRows() { return rows; }
int AroyaReader::getColumns() { return columns; }

void AroyaReader::discrete(const int&column) {
	int i, j, nums = 0;
	bool exists = false;
	//ͳ����������
	vector<string>tables;
	for (i = 1; i < rows; i++) {
		//�Ƿ���tables���Ѵ���
		exists = false;
		for (j = 0; j < nums; j++) {
			if (data[column][i] == tables[j]) {
				exists = true;
				break;
			}
		}
		//�����������
		if (!exists) {
			tables.push_back(data[column][i]);
			nums++;
		}
	}

	//�������
	//����������
	for (i = 0; i < nums; i++)data[0].push_back(tables[i]);
	//ÿ�д�����0��������Ϊ1
	for (i = 1; i < rows; i++) {
		for (j = 0; j < nums; j++) {
			if (data[i][column] == tables[j])data[i].push_back("1");
			else data[i].push_back("0");
		}
		//���ԭ������
		data[i].erase(data[i].begin()+column);
	}
	//����������Ϣ
	columns += nums;
	columns -= 1;
}

void AroyaReader::discrete() {
	bool toDiscrete;
	for (int j = 1; j < columns; j++) {
		toDiscrete = false;
		//���ڸ�ʽת����
		//δ���
		//����������ת��ɢֵ
		if (NotPureNumber(data[1][j])) {
			discrete(j);
			j--;//j++ after this
		}
	}
}

bool static NotPureNumber(const string&str) {
	int i, l = str.length();
	char left = '0' - 1, right = '9' + 1;
	bool point = true;
	for (i = 0; i < l; i++) {
		if (point&& str[i] > left &&str[i] < right) {
			if (str[i] == ',')point = false;
		}
		else return true;
	}
	return false;
}
bool static PureNumber(const char&t) {
	return t >= '0'&&t <= '9';
}

void AroyaReader::setTableName(const char*origin, const char*new_) {
	data[0][findTable(origin)] = new_;
}
void AroyaReader::deleteColumn(const int&col) {
	for (int i = 0; i < rows; i++) {
		data[i].erase(data[i].begin() + col);
	}
}
void AroyaReader::deleteRow(const int&row) {
	data.erase(data.begin() + row);
}

void AroyaReader::dispartTime(const char*tableName,const bool&flag) {
	int column = findTable(tableName);
	AroyaDate date;

	//table
	data[0].push_back("month");
	data[0].push_back("weekday");

	//temp str
	string str;
	for (int i = 1; i < getRows(); i++) {
		date.input(data[i][column]);
		//clear stringstream
		internalSst.str("");
		internalSst.clear();
		//get Month
		internalSst << date.getMonth();
		internalSst >> str;
		data[i].push_back(str);
		//clear stringstream
		internalSst.str("");
		internalSst.clear();
		//get Weekday
		internalSst << date.getWeekday();
		internalSst >> str;
		data[i].push_back(str);
	}
	//ɾ��ԭ������
	if (flag)deleteColumn(column);
}