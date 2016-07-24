#include "record.h"


/*
bool hasReturned;       //是否已归还
string bookIsbn;        //图书编号
string readerId;        //读者编号
date loanDate;          //借出日期
date dueDate;           //应还日期
date returnDate;        //归还日期
string loanOperator;    //借出操作员
string returnOperator;  //归还操作员
*/

void record::init(string & str)
{
	stringstream ss;
	int start = 0;
	int pos;


	while (pos = str.find('\n') != string::npos)
		str.erase(pos);

	pos = str.find(',');
	ss << str.substr(start, pos);
	ss >> hasReturned;
	ss.clear();
	start = pos + 1;

	pos = str.find(start, ',');
	bookIsbn = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	readerId = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	pos = str.find(pos + 1, ',');
	pos = str.find(pos + 1, ',');
	loanDate = date(str.substr(start, pos));
	start = pos + 1;

	pos = str.find(start, ',');
	pos = str.find(pos + 1, ',');
	pos = str.find(pos + 1, ',');
	dueDate = date(str.substr(start, pos));
	start = pos + 1;

	pos = str.find(start, ',');
	pos = str.find(pos + 1, ',');
	pos = str.find(pos + 1, ',');
	returnDate = date(str.substr(start, pos));
	start = pos + 1;

	pos = str.find(start, ',');
	loanOperator = str.substr(start, pos);
	start = pos + 1;

	recedeOperator = str.substr(start);
}

record::record(string & isbn, string & reader)
{
	bookIsbn = isbn;
	readerId = reader;
}


void record::loan(string & operatorID)
{

	loanOperator = operatorID;
	hasReturned = false;
	loanDate = date::currentDate();
	dueDate = loanDate + 30;
}

void record::recede(string & operatorID)
{
	hasReturned = true;
	returnDate = date::currentDate();
	recedeOperator = operatorID;
}



bool record::operator==(const record & rd) const
{
	return bookIsbn == rd.bookIsbn && readerId == rd.readerId;
}



string record::toString()
{
	stringstream ss;
	ss << hasReturned << ',' << bookIsbn << ',' << readerId << ',' << loanDate.toString() << ','
		<< dueDate.toString() << ',' << returnDate.toString() << ',' << loanOperator << ',' << recedeOperator;
	return ss.str();
}

