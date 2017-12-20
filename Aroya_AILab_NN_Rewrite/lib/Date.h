#ifndef AROYA_DATE
#define AROYA_DATE
class AroyaDate {
public:
	AroyaDate();
	/*date format
	YYYY?MM?DD
	?是任何非数字字符
	*/
	void input(const string&dateStr);
	//获取星期
	int getWeekday();
	//获取与标准时间的日期差
	int getDateInstant();
	//获取月份
	int getMonth();
private:
	int year, month, day, weekday;
	const static int StartYear = 2000;
	const static int StartMonth = 1;
	const static int StartDay = 1;
	const static int StartWeekday = 6;
};
#endif // !AROYA_DATE
