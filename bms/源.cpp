#include "data.h"
#include <Windows.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;


li::data d;
person manager(string("0000"), string("1234"));


void login()
{
	string id;
	string password;
	
	cout << "                    Login     in                       " << endl;
	cout << "ManagerID:";
	cin >> id;
	cout << "\nPassword:";
	cin >> password;
	person temp(id, password);

	if (temp == manager)
		return;


	auto re = d.find(temp);
	if (re.empty())
	{

		cout << "           Wrong username or password! " << endl;
		Sleep(1500);
		system("cls");
		login();
	}
	else
	{
		manager = re.front();
	}
}

void loanBooks()
{
	string isbn;
	char ch;
	system("cls");
	cout << "                 Loan Books                 " << endl;
	cout << "ISBN:";
	cin >> isbn;
	book bk(isbn);
	auto re = d.find(bk);
	if (re.empty())
	{
		cout << "There is no objective Books!" << endl;
		cout << "Continue?(y/n)" << endl;
		cin >> ch;
		cin.clear();
		if (ch != 'y' || ch != 'Y')
			return;
		else
		{
			loanBooks();
			return;
		}
	}


	string readerID;
	string password;
	while (true)
	{
		cout << "ReaderID:";
		cin >> readerID;
		cout << "Password:";
		cin >> password;
		person reader(readerID, password);
		auto re = d.find(reader);
		if (re.empty())
		{
			cout << "           Wrong username or password! " << endl;
			cout << "Continue?(y/n)" << endl<<endl;
			cin >> ch;
			cin.clear();
			if (ch != 'y' || ch != 'Y')
				return;
		}
		else
		{
			break;
		}
	}
	
	record rd(isbn,readerID);
	rd.loan(manager.personID());
	d.insert(rd);
}

void recedeBooks()
{
	system("cls");
	cout << "                   RecedeBooks                   " << endl;

	cout << "ISBN:";
	string isbn;
	cin >> isbn;
	cout << "ReaderID:";
	string reader;
	cin >> reader;

	record rd(isbn, reader);
	char ch;
	auto re = d.find(rd);
	if (re.empty())
	{
		cout << "              There is no record!" << endl;
		cout << "Continue?(y/n)" << endl << endl;
		cin >> ch;
		cin.clear();
		if (ch != 'y' || ch != 'Y')
			return;
		else
		{
			recedeBooks();
			return;
		}
	}

	rd = re.front();
	record fresh = rd;
	fresh.recede(manager.personID());
	d.modify(rd, fresh);
}

void addBooks()
{
	system("cls");
	cout << "                            AddBooks  " << endl;
	cout << "ISBN:";
	string isbn;
	cin >> isbn;
	book bk(isbn);
	auto re = d.find(bk);
	if (!re.empty())
	{
		cout << "          This book has exit!" << endl;
		cout << "Try again?(y/n)" << endl;
		char ch;
		cin >> ch;
		cin.clear();
		if (ch != 'y' || ch != 'Y')
			return;
		else
		{
			addBooks();
			return;
		}
		
	}

	int typeId;
	cout << "TypeID:";
	cin >> typeId;

	string name;
	cout << "Name:";
	cin >> name;

	string writer;
	cout << "Writer:";
	cin >> writer;

	string translator;
	cout << "Translator:";
	cin >> translator;

	string publisher;
	cout << "Publisher:";
	cin >> publisher;

	char ch;
	unsigned year, month, day;
	cout << "PublicationDate(year,month,day):";
	cin >> year >> ch >> month >> ch >> day;
	date pd(year, month, day);

	float price;
	cout << "Price;";
	cin >> price;

	book b(isbn, typeId, name, writer, translator, publisher, pd, price);

	d.insert(b);
}



void addReaders()
{
	system("cls");
	cout << "                          AddReaders" << endl;
	int age;
	cout << "Age:";
	cin >> age;

	string ic;
	cout << "IdentityCard:";
	cin >> ic;

	string name;
	cout << "Name:";
	cin >> name;

	string sex;
	cout << "Sex:";
	cin >> sex;

	string tel;
	cout << "Tel:";
	cin >> tel;

	int id;
	string strId;
	id = d.readerNum();
	stringstream ss;
	ss << id;
	ss >> strId;

	string password;
	cout << "Password:";
	cin >> password;

	person p(true, age,ic, name, sex, tel,strId, password);

	d.insert(p);

}

void addManagers()
{
	system("cls");
	cout << "                          AddReaders" << endl;
	int age;
	cout << "Age:";
	cin >> age;

	string ic;
	cout << "IdentityCard:";
	cin >> ic;

	string name;
	cout << "Name:";
	cin >> name;

	string sex;
	cout << "Sex:";
	cin >> sex;

	string tel;
	cout << "Tel:";
	cin >> tel;

	int id;
	string strId;
	id = d.readerNum();
	stringstream ss;
	ss << id;
	ss >> strId;

	string password;
	cout << "Password:";
	cin >> password;

	person p(false, age, ic, name, sex, tel, strId, password);

	d.insert(p);
}

void modifyInfor()
{
	system("cls");

	cout << "                      Unimplemented feature!";
	Sleep(1500);
}

void exitSystem()
{
	d.save();
}



void menu()
{
	char ch;
	system("cls");
	cout << "                1.Loan books" << endl;
	cout << "                2.Return books" << endl;
	cout << "                3.Add books" << endl;
	cout << "                4.Add readers" << endl;
	cout << "                5.Add managers" << endl;
	cout << "                6.Modify information" << endl;
	cout << "                0.exit" << endl;
	cin >> ch;
	cin.clear();
	system("cls");
	switch (ch)
	{
	case '1':
		loanBooks();
		break;
	case '2':
		recedeBooks();
		break;
	case '3':
		addBooks();
		break;
	case '4':
		addReaders();
		break;
	case '5':
		addManagers();
		break;
	case '6':
		modifyInfor();
		break;
	case '0':
		exitSystem();
		break;
	default:
		break;
	}
	system("cls");
	menu();
}



int main()
{

	login();
	menu();

	std::cin.get();
	return 0;
}


