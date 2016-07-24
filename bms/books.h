#ifndef _BOOKS_H_
#define _BOOKS_H_
#include <string>
#include <set>
#include "date.h"
using namespace std;



class book
{
private:
	string isbn;                       //ͼ����
	int typeId;                        //�����
	string name;                       //ͼ������
	string writer;                     //����
	string translator;                 //����
	string publisher;                  //������
	date   publicationData;            //��������
	float price;                       //�鼮�۸�

	

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


