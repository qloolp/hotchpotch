


#include "bookType.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include "books.h"
using namespace std;
// -------------------booksType----------------------



bookType::bookType(string typeName, int days, float fine)
{
	this->typeName = typeName;
	this->days = days;
	this->fine = fine;
}

bookType::bookType()
{
	id = -1;
	typeName = "";
	days = 0;
	fine = 0.0;
}


bookType::bookType(string& str)
{
	int start = 0;
	int pos;
	stringstream ss;
	pos = str.find(',');
	ss << str.substr(start, pos);
	ss >> id;
	ss.clear();

	start = pos + 1;
	pos = str.find(',', pos + 1);
	ss << str.substr(start, pos);
	ss >> typeName;
	ss.clear();

	start = pos + 1;
	pos = str.find(',', pos + 1);
	ss << str.substr(start, pos);
	ss >> days;
	ss.clear();

	start = pos + 1;
	ss << str.substr(start);
	ss >> fine;
}



bookType bookType::getBookType(int typeId, set<bookType>& typeSet)
{
	for each (auto var in typeSet)
	{
		if (var.id == typeId)
			return var;
	}
	return bookType();

}


bool bookType::operator==(const bookType & bt)const
{
	return bt.typeName == this->typeName;
}


string bookType::toString()
{
	stringstream str;
	str << this->id << ',' << this->typeName << ',' << this->days << ',' << this->fine;
	return str.str();
}


bool bookType::operator<(const bookType & bt) const
{
	return false;
}


