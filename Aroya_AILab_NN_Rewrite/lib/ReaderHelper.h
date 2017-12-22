#ifndef Aroya_READER_HELPER
#define Aroya_READER_HELPER

#include<vector>
#include<fstream>
using namespace std;
#include"Reader.h"

class AroyaReaderHelper {
public:
	AroyaReaderHelper();
	//insert table
	
	//if not input myTableName, will set it as same as tableName
	void insert(AroyaReader&reader, const char*tableName, const char*myTableName=nullptr);
	//insert by column position
	void insert(AroyaReader&reader, const int&col);
	//for AroyaKMeans to load
	vector<vector<double>> getData();
	//归一化
	void normalization();
	//写出数据
	void writeFile(const char*fileName);
private:
	int findTable(const char*tableName);
	vector<string>table;
	vector<vector<double>>buffer;
	vector<double>empty;
};



#endif