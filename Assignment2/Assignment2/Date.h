/*
 name :: Date.h
 detail :: header file 
*/
#ifndef _Date_h
#define _Date_h

#include<string>


using namespace std;

enum Month{
		JANUARY = 1,FEBRUARY,MARCH,APRIL,MAY,JUNE,JULY,AUGUST,SEPTEMBER,OCTOBER,NOVEMBER,DECEMBER
	};

class Date{
public:
	//conductor
	Date();
	Date(Month,int,int);
	Date(int,Month,int);
	Date(int,int,Month);
	//get
	int getDay();
	string getMonth();
	int getYear();
	//tostring
	string toString();
	//daysInMonth
	int daysInMonth(Month,int);
	//isLeapYear
	bool isLeapYear(int);
	//monthToString
	string monthToString(Month);
	//operator
	bool operator==(Date);
	bool operator!=(Date);
	bool operator<(Date);
	bool operator>(Date);
	bool operator<=(Date);
	bool operator>=(Date);
	Date operator+(int) ;
	Date operator-(int);
	Date operator+=(int);
	Date operator-=(int);
	Date operator++();
	Date operator++(int);
	Date operator--();
	Date operator--(int);
	int operator-(Date);
	int getTotalDay(Date);

private:
	int day;
	int years;
	Month in_month;
};

ostream & operator<<(ostream & os, Date date_os);

#endif



