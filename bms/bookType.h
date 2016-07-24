#pragma once
#include <string>
#include <set>
#include "date.h"
using namespace std;


class bookType
{
private:
	int id;                                 //ͼ�������
	string typeName;                        //ͼ���������
	int days;                               //�ɽ�����
	float fine;                             //����ÿ�շ�����

	bookType(string typeName, int days, float fine);

	

public:
	bookType();
	bookType(string& str);
	bookType getBookType(int typeId,set<bookType>& typeSet);
	bool operator==(const bookType& bt) const;
	bool operator<(const bookType& bt) const;
	string toString();
};

