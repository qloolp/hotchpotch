#pragma once
#include <string>
#include <set>
#include "date.h"
using namespace std;


class bookType
{
private:
	int id;                                 //图书类别编号
	string typeName;                        //图书类别名称
	int days;                               //可借天数
	float fine;                             //逾期每日罚款数

	bookType(string typeName, int days, float fine);

	

public:
	bookType();
	bookType(string& str);
	bookType getBookType(int typeId,set<bookType>& typeSet);
	bool operator==(const bookType& bt) const;
	bool operator<(const bookType& bt) const;
	string toString();
};

