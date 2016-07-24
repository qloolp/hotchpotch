#ifndef  _DATE_H_
#define _DATE_H_
#include <ctime>
#include <string>
#include <sstream>
using namespace std;


class date
{
private:
	unsigned year;
	unsigned month;
	unsigned day;
	bool leap();
	
public:
	date() :year(0), month(0), day(0) {}
	date(string& str);
	date(unsigned y, unsigned m, unsigned d) :year(y), month(m), day(d) {}
	static date currentDate();
	date operator+(int days);
	date friend operator+(int n, date& d);
	string toString();
	bool operator==(const date& d)const;
};


#endif // ! _DATE_H_

