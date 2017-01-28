
#include "stdafx.h"
#include <conio.h> 
#include <string.h> 
#include <iostream> 

using namespace std;

struct date // дата рождения 
{
	char daymon[6];
	int year;
};
//=======     class Student    ===============
class Book {
	char name[30]; //private 
	char avtor[30];
	char izdat[20];
	int god;
	int kol; // кол страниц
public:
	Book();
	char *getavtor();
	char *getizdat();
	int getgod();
	void show();
};
Book::Book()
{
	cout << "Input naim :"; cin >> name;
	cout << "Input avtor \n"; cin >> avtor;
	cout << "Input izdat:";  cin >> izdat;
	cout << "Input year:";  cin >> god;
	cout << "Input kol of str:"; cin >> kol;
}
void Book::show()
{
	cout << "Naim      :" << name << endl;
	cout << "Avtor     :" << avtor << endl;
	cout << "Izdat     :" << izdat << endl;
	cout << "Year      :" << god << endl;
	cout << "Kol       :" << kol << endl;
}
char *Book::getavtor() { return avtor; }
char *Book::getizdat() { return izdat; }
int Book::getgod() { return god; }
void spisavtor(Book spis[], int n)//список книг  заданного автора
{
	char avt[20];
	cout << "Input avtor:";  cin >> avt;
	for (int i = 0; i<n; i++)
		if (strcmp(spis[i].getavtor(), avt) == 0)spis[i].show();
}

void spisizdat(Book spis[], int n)//список книг  заданного bplfntkmcndf
{
	char avt[20];
	cout << "Input iazdat:";  cin >> avt;
	for (int i = 0; i<n; i++)
		if (strcmp(spis[i].getizdat(), avt) == 0)spis[i].show();
}
void spisgod(Book spis[], int n)
//список книг после зад. года 
{
	int i, k;
	char fac[20];
	cout << "Input year:";  cin >> k;
	for (i = 0; i<n; i++)
		if (spis[i].getgod() >= k)
			spis[i].show();
}

int _tmain(int argc, _TCHAR* argv[])
{
	Book *spis;
	int n;
	cout << "Input a number of books: "; cin >> n;
	spis = new Book[n];
	for (int i = 0; i<n; i++) {
		cout << "==============================" << endl;
		spis[i].show();
	}
	spisavtor(spis, n);
	spisizdat(spis, n);
	spisgod(spis, n);
	delete[] spis;
	cout << "press any key!";
	while (!kbhit());
	return 0;
}
