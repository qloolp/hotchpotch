#include "person.h"
#include <sstream>

void person::init(string & str)
{
	stringstream ss;
	int start = 0;
	int pos;

	pos = str.find(start,',');
	ss << str.substr(start, pos);
	ss >> isReader;
	start = pos + 1;

	pos = str.find(start, ',');
	ss << str.substr(start, pos);
	ss >> age;
	start = pos + 1;
	
	pos = str.find(start,',');
	identityCard = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	name =  str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	sex = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	tel = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	id = str.substr(start, pos);
	start = pos + 1;

	password = str.substr(start);
}

person::person(string & id, string & password, string& identityCard)
{
	this->id = id;
	this->password = password;
	this->identityCard = identityCard;
}

person::person()
{
}

person::person(bool isr, int age, string & ic, string & na, string & se, string & te, string & id, string & pa)
{
	isReader = isr;
	this->age = age;
	identityCard = ic;
	name = na;
	sex = se;
	tel = te;
	this->id = id;
	password = pa;
}

string person::toString()
{
	stringstream ss;
	ss << isReader << ',' << age << ',' << identityCard << ',' << name << ',' 
		<< sex << ',' << tel << ',' << id << ',' << password;
		return ss.str();
}

person::person(string & ic)
{
	this->identityCard = ic;
}

bool person::operator==(const person & p)
{
	return this->id == p.id;
}

string person::personID()
{
	return id;
}

string person::personPassword()
{
	return password;
}



