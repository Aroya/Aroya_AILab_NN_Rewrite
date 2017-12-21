#ifndef Aroya_READER_HELPER
#define Aroya_READER_HELPER

#include<vector>
#include"Reader.h"
using namespace std;

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
	//πÈ“ªªØ
	void normalization();
private:
	int findTable(const char*tableName);
	vector<string>table;
	vector<vector<double>>buffer;
	vector<double>empty;
};



#endif