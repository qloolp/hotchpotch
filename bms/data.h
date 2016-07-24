#pragma once
#include <string>
#include <vector>
#include "books.h"
#include "person.h"
#include "bookType.h"
#include "record.h"
using std::string;
using std::vector;

namespace li
{

	class data
	{
	private:
		static string bookTypesPath;
		static string booksPath;
		static string recordsPath;
		static string peoplePath;

		vector<book> books;
		vector<bookType> types;
		vector<record> records;
		vector<person> people;

	public:
		data();
		data(string& btp, string& bp, string& rp, string& pp);
		~data();
		const vector<bookType> find(const bookType& bt);
		const vector<book> find(const book bk);
		const vector<record> find(const record& rd);
		const vector<person> find(const person& p);

		void insert(bookType& bt);
		void insert(book& bk);
		void insert(record& rd);
		void insert(person& p);

		void modify(bookType& old, bookType& fresh);
		void modify(book& old, book& fresh);
		void modify(record& old, record& fresh);
		void modify(person& old, person& fresh);


		int readerNum();
		void save();
	};

}