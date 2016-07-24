#include "books.h"
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

//---------------------books--------------



string book::toString()
{
	stringstream str;
	str << isbn << ',' << typeId << ',' << name << ',' << writer << ',' 
		<< translator << ',' << publisher << ',' << publicationData.toString() << ',' << price;
	return str.str();
}


book::book(string & isbn)
{
	this->isbn = isbn;
}

book::book()
{
}

bool book::operator==(const book& b) const
{
	return b.isbn == isbn;
}


bool book::operator<(const book & b) const
{
	return false;
}

book::book(string & isbn, int typeId, string & name, string & writer, string & translator, string & publisher, date & pubDate, float price)
{
	this->isbn = isbn;
	this->typeId = typeId;
	this->name = name;
	this->writer = writer;
	this->translator = translator;
	this->publisher = publisher;
	this->publicationData = pubDate;
	this->price = price;
}


void book::init(string& str)
{
	stringstream ss;
	int start = 0;
	int pos;

	while (pos = str.find('\n') != string::npos)
		str.erase(pos);


	pos = str.find(',');
	isbn = str.substr(0, pos);
	start = pos+1;

	pos = str.find(start, ',');
	ss << str.substr(start,pos);
	ss >> typeId;
	ss.clear();
	start = pos + 1;

	pos = str.find(start, ',');
	name = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	writer = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	translator = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	publisher = str.substr(start, pos);
	start = pos + 1;

	pos = str.find(start, ',');
	pos = str.find(pos+1, ',');
	pos = str.find(pos+1, ',');
	publicationData = date(str.substr(start, pos));
	start = pos + 1;

	ss << str.substr(start, pos);
	ss >> price;
}
