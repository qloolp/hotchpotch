#ifndef _RECORD_H_
#define _RECORD_H_
#include <string>
#include <vector>
#include "person.h"
#include "bookType.h"
#include "date.h"
using namespace std;

class record
{
private:
	bool hasReturned;       //是否已归还
	string bookIsbn;        //图书编号
	string readerId;        //读者编号
	date loanDate;          //借出日期
	date dueDate;           //应还日期
	date returnDate;        //归还日期
	string loanOperator;    //借出操作员
	string recedeOperator;  //归还操作员
public:
	void init(string& str);
	record() {};
	record(string& isbn, string& reader);
	void loan(string& operatorID);
	void recede(string& operatorID);
	bool operator==(const record& rd) const;
	string toString();
};

#endif
