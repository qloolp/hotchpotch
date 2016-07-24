#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <sstream>
using namespace std;

class person
{
private:
	bool isReader;
	int age;                //年龄
	string identityCard;    //证件号码
	string name;            //姓名
	string sex;             //性别
	string tel;             //电话号码
	string id;              //读者编号或操作员编号
	string password;
public:
	void init(string& str);
	person(string& id, string& password, string& identityCard=string("19950202"));
	person();
	person(bool isr, int age, string& ic, string& na, string& se, string& te, string& id, string& pa);
	string toString();
	person(string& ic);
	bool operator==(const person& p);
	string personID();
	string personPassword();
};



#endif
