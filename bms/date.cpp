#include "date.h"

bool date::leap()
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )
		return true;
	else 
		return false;
}

string date::toString()
{
	stringstream ss;
	ss << year << ',' << month << ',' << day;
	return ss.str();
}

bool date::operator==(const date & d) const
{
	return year == d.year && month == d.month && day == d.day;
}

date::date(string & str)
{
	stringstream ss;
	int start = 0;
	int pos;
	pos = str.find(',');
	ss << str.substr(pos);
	ss >> year;
	ss.clear();

	start = pos + 1;
	pos = str.find(',', start);
	ss << str.substr(start, pos);
	ss >> month;
	ss.clear();

	ss << str.substr(pos + 1);
	ss >> day;

}

date date::currentDate()
{

	time_t t = time(0);
	struct tm* now=nullptr;
	localtime_s(now, &t);
	int y = now->tm_year + 1990;
	int m = now->tm_mon+1;
	int d = now->tm_mday;
	return date(y,m,d);
}

date date::operator+(int n)
{
	int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	date d(year, month, day);
	while (n > 0)
	{
		if (n > days[month - 1]-d.day)
		{
			if (d.leap())
				days[1] = 29;
			else
				days[1] = 28;

			d.month = d.month == 12 ? 1, d.year++ : d.month++;
			d.day = 1;

			n -= days[month - 1] - d.day;
		}
		else
		{
			d.day += n;
		}
	}
	return d;
}

date operator+(int n, date& d)
{
	date re(d.year,d.month,d.day);
	return re + n;
}
