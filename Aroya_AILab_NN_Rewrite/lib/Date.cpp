#include<string>
#include<sstream>
using namespace std;
#include"Date.h"

bool static PureNumber(const char&);

AroyaDate::AroyaDate(){
	//empty
}
void AroyaDate::input(const string&str) {
	string buffer;
	stringstream sst;
	char temp;
	int position = 0;
	int i, l = str.length;
	//读取年月日
	for (i = 0; i < l; i++) {
		if (PureNumber(temp = str[i])) {
			buffer += temp;
		}
		else {
			sst.str(buffer);
			sst.clear();
			switch (position)
			{
			case 0:
				sst >> year;
				break;
			case 1:
				sst >> month;
				break;
			default:
				sst >> day;
				break;
			}
			position++;
			buffer.clear();
		}
	}
	//计算日期差instant和weekday
	instant = 0;
	for (i = StartYear; i < year; i++) {
		if (i % 100 && !(i % 4)) {
			instant += 366;
		}
		else if (!(i % 400)) {
			instant += 366;
		}
		else instant += 365;
	}
	for (i = StartMonth; i < month; i++) {
		switch (i)
		{
		case 1:
			instant += January;
			break;
		case 2:
			//特殊情况
			break;
		case 3:
			instant += March;
			break;
		case 4:
			instant += April;
			break;
		case 5:
			instant += May;
			break;
		case 6:
			instant += June;
			break;
		case 7:
			instant += July;
			break;
		case 8:
			instant += August;
			break;
		case 9:
			break;
		default:
			break;
		}
	}
}

bool static PureNumber(const char&t) {
	return t >= '0'&&t <= '9';
}