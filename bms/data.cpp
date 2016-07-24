#pragma once
#include "data.h"
#include <fstream>
using namespace std;

namespace li
{

	string data::bookTypesPath = "types.txt";
	string data::booksPath = "books.txt";
	string data::recordsPath = "records.txt";
	string data::peoplePath = "people.txt";


	data::data()
	{
		// load bookType
		string str;
		ifstream finbt(bookTypesPath);
		while (finbt >> str)
		{
			types.push_back(bookType(str));
		}
		finbt.close();

		ifstream finbk(booksPath);
		while (finbk >> str)
		{
			book bk;
			bk.init(str);
			books.push_back(bk);
		}
		finbk.close();

		ifstream finrec(recordsPath);
		while (finrec >> str)
		{
			record rd;
			rd.init(str);
			records.push_back(rd);
		}
		finrec.close();

		ifstream finp(peoplePath);
		while (finp >> str)
		{
			person p;
			p.init(str);
			people.push_back(p);
		}
		finp.close();

	}

	data::data(string & btp, string & bp, string & rp, string& pp)
	{
		bookTypesPath = btp;
		booksPath = bp;
		recordsPath = rp;
		peoplePath = pp;
	}

	data::~data()
	{
	}

	const vector<bookType> data::find(const bookType & bt)
	{
		// TODO: 在此处插入 return 语句
		auto it = std::find(types.begin(), types.end(), bt);
		auto v = vector<bookType>();
		if (it != types.end())
		{
			v.push_back(*it);
		}
		return v;
	}

	const vector<book> data::find(const book bk)
	{
		// TODO: 在此处插入 return 语句
		auto it = std::find(books.begin(), books.end(), bk);
		auto v = vector<book>();
		if (it != books.end())
		{
			v.push_back(*it);
		}
		return v;
	}

	const vector<record> data::find(const record & rd)
	{
		// TODO: 在此处插入 return 语句
		auto it = std::find(records.begin(), records.end(), rd);
		auto v = vector<record>();
		if (it != records.end())
		{
			v.push_back(*it);
		}
		return v;
	}

	const vector<person> data::find(const person & p)
	{
		auto it = std::find(people.begin(), people.end(), p);
		auto v = vector<person>();
		if (it != people.end())
		{
			v.push_back(*it);
		}
		return v;
	}

	void data::insert(bookType & bt)
	{
		auto it = std::find(types.begin(), types.end(), bt);
		if (it == types.end())
		{
			types.push_back(bt);
		}
	}

	void data::insert(book & bk)
	{
		auto it = std::find(books.begin(), books.end(), bk);
		if (it == books.end())
		{
			books.push_back(bk);
		}
	}

	void data::insert(record & rd)
	{
		auto it = std::find(records.begin(), records.end(), rd);
		if (it == records.end())
		{
			records.push_back(rd);
		}
	}

	void data::insert(person & p)
	{
		auto it = std::find(people.begin(), people.end(), p);
		if (it == people.end())
		{
			people.push_back(p);
		}
	}

	void data::modify(bookType & old, bookType & fresh)
	{
		auto it = std::find(types.begin(), types.end(), old);
		if (it != types.end())
		{
			*it = fresh;
		}
	}

	void data::modify(book & old, book & fresh)
	{
		auto it = std::find(books.begin(), books.end(), old);
		if (it != books.end())
		{
			*it = fresh;
		}
	}

	void data::modify(record & old, record & fresh)
	{
		auto it = std::find(records.begin(), records.end(), old);
		if (it != records.end())
		{
			*it = fresh;
		}
	}

	void data::modify(person & old, person & fresh)
	{
		auto it = std::find(people.begin(), people.end(), old);
		if (it != people.end())
		{
			*it = fresh;
		}
	}

	int data::readerNum()
	{
		return people.size();
	}

	void data::save()
	{
		ofstream fob(booksPath);
		for each (book var in books)
		{
			fob << var.toString() << endl;
		}
		fob.close();

		ofstream fobt(bookTypesPath);
		for each (bookType var in types)
		{
			fobt << var.toString() << endl;
		}
		fobt.close();

		ofstream fore(recordsPath);
		for each (record var in records)
		{
			fore << var.toString() << endl;
		}
		fore.close();

		ofstream fope(peoplePath);
		for each (person var in people)
		{
			fope << var.toString() << endl;
		}
		fope.close();
	}

}