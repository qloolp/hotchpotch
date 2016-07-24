#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <sstream>
using namespace std;

class person
{
private:
	bool isReader;
	int age;                //����
	string identityCard;    //֤������
	string name;            //����
	string sex;             //�Ա�
	string tel;             //�绰����
	string id;              //���߱�Ż����Ա���
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
