#ifndef _BOOKS_H_
#define _BOOKS_H_
#include <string>
#include <set>
#include "date.h"
using namespace std;



class book
{
private:
	string isbn;                       //图书编号
	int typeId;                        //类别编号
	string name;                       //图书名称
	string writer;                     //作者
	string translator;                 //译者
	string publisher;                  //出版社
	date   publicationData;            //出版日期
	float price;                       //书籍价格

	

public:
	string toString();
	book(string& isbn);
	book();
	bool operator==(const book& b) const;
	void init(string& str);
	bool operator<(const book& b) const;
	book(string& isbn, int typeId, string& name, string& writer, string& translator, string& publisher, date& pubDate, float price);
};





#endif // !_BOOKS_H_


