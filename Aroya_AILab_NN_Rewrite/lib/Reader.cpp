#include"Reader.h"

//仅依据不包含数字、小数点来判断
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
		//数据结束 处理数据
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
		//无分隔符 记录数据
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
	//统计类型数量
	vector<string>tables;
	for (i = 1; i < rows; i++) {
		//是否在tables中已存在
		exists = false;
		for (j = 0; j < nums; j++) {
			if (data[column][i] == tables[j]) {
				exists = true;
				break;
			}
		}
		//不存在则加入
		if (!exists) {
			tables.push_back(data[column][i]);
			nums++;
		}
	}

	//添加数据
	//首行列名称
	for (i = 0; i < nums; i++)data[0].push_back(tables[i]);
	//每行存在则0，不存在为1
	for (i = 1; i < rows; i++) {
		for (j = 0; j < nums; j++) {
			if (data[i][column] == tables[j])data[i].push_back("1");
			else data[i].push_back("0");
		}
		//清除原数据列
		data[i].erase(data[i].begin()+column);
	}
	//更新列数信息
	columns += nums;
	columns -= 1;
}

void AroyaReader::discrete() {
	bool toDiscrete;
	for (int j = 1; j < columns; j++) {
		toDiscrete = false;
		//日期格式转日期
		//未完成
		//非连续数字转离散值
		if (NotPureNumber(data[1][j])) {
			discrete(j);
			j--;//j++ after this
		}
	}
}

bool static NotPureNumber(const string&str) {
	int i, l = str.length;
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
void AroyaReader::deleteTable(const int&col) {
	for (int i = 0; i < rows; i++) {
		data[i].erase(data[i].begin() + col);
	}
}
void AroyaReader::deleteRow(const int&row) {
	data.erase(data.begin() + row);
}