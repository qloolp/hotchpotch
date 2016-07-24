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
	bool hasReturned;       //�Ƿ��ѹ黹
	string bookIsbn;        //ͼ����
	string readerId;        //���߱��
	date loanDate;          //�������
	date dueDate;           //Ӧ������
	date returnDate;        //�黹����
	string loanOperator;    //�������Ա
	string recedeOperator;  //�黹����Ա
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
