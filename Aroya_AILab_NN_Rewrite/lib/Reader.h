#ifndef	Aroya_READER
#define Aroya_READER
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>

using namespace std;

//ʱ�������
#define START_DAY 1
#define START_MONTH 1
#define START_YEAR 2000

class AroyaReader {
private:
	vector<vector<string>>data;		//ȫ����string�ݴ�
	stringstream internalSst;		//ת��ʹ��
	int rows, columns;
public:
	AroyaReader();
	void read(const char*fileName);
	string getStringData(const int&rows, const int&columns);
	double getDoubleData(const int&rows, const int&columns);
	int findTable(const char*tableName);
	int getRows();
	int getColumns();
	void setTableName(const char*origin, const char*new_);
	void deleteTable(const int&col);

	//��ֵ����:ɾ����ֵ��
	void deleteRow(const int&row);
	//���������֡���ɢtable
	void discrete(const int&column);
	//�Զ����������У��Զ�ת���з�����������Ϊ��ɢ����
	void discrete();
};

#endif