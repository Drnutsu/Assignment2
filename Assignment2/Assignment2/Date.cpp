/*
name :: Date.cpp
details : : implementation
*/
#include <iostream>
#include <string>
#include "Date.h"
#include<sstream>

using namespace std;

string IntToString(int num);
string Firstupper(string str);

Date::Date(){
	day = 1;
	in_month = JANUARY;
	years = 2000;
}

Date::Date(Month m,int in_1,int in_2){
	in_month = m;
	if(in_1 > in_2) {
		day = in_2;
		years = in_1;
	}
	else {
		day = in_1;
		years = in_2;
	}
}

Date::Date(int in_1,Month m,int in_2){
	in_month = m;
	if(in_1 > in_2) {
		day = in_2;
		years = in_1;
	}
	else {
		day = in_1;
		years = in_2;
	}
}

Date::Date(int in_1,int in_2,Month m){
	in_month = m;
	if(in_1 > in_2) {
		day = in_2;
		years = in_1;
	}
	else {
		day = in_1;
		years = in_2;
	}
}

int Date::getDay(){
	return day;
}

int Date::getYear(){
	return years;
}

string Date::getMonth(){
	return monthToString(in_month);
}

string Date::monthToString(Month in_x){
	if(in_x == 1) return "JANUARY";
	if(in_x == 2) return "FEBRUARY";
	if(in_x == 3) return "MARCH";
	if(in_x == 4) return "APRIL";
	if(in_x == 5) return "MAY";
	if(in_x == 6) return "JUNE";
	if(in_x == 7) return "JULY";
	if(in_x == 8) return "AUGUST";
	if(in_x == 9) return "SEPTEMBER";
	if(in_x == 10) return "OCTOBER";
	if(in_x == 11) return "NOVEMBER";
	if(in_x == 12) return "DECEMBER";
	return "Out oF BoUnD";
}

string Date::toString(){

	string str = IntToString(day) + "-" + Firstupper(getMonth().substr(0,3))+"-"+IntToString(years);
	return str;
}

int Date::daysInMonth(Month m,int year){
	if(m == JANUARY || m == MARCH || m == MAY || m == JULY || m == AUGUST || m == OCTOBER || m == DECEMBER) return 31;
	if(m == APRIL || m == JUNE || m == SEPTEMBER || m == NOVEMBER) return 30;
	if(m == FEBRUARY){
		if(isLeapYear(year)) return 29;
		else return 28;
	}
	return 0;
}

bool Date::isLeapYear(int year){
	if(year%400 == 0) return true;
	if(year%4 == 0 && year%100 != 0) return true;
	else return false;
}

string IntToString(int num){
	stringstream stream;
	stream<<num;
	return stream.str();
}

string Firstupper(string str){
	for(int i = 1;i<3;i++){
		str[i] = tolower(str[i]);
	}
	return str;
}

ostream & operator<<(ostream & os, Date date_os){
	return os << date_os.toString();
}

bool Date::operator==(Date input){
	return input.day == this->day && input.in_month == this->in_month && input.years == this->years;

}

bool Date::operator!=(Date input){
	
	return input.day != day || input.in_month != in_month || input.years != years;

}

bool Date::operator<(Date input){
	
	if(years < input.years) return true;
	if(input.years < years) return false;
	if(in_month < input.in_month) return true;
	if(in_month < input.in_month) return false;
	if(day < input.day) return true;
	if(day < input.day) return false;
	return false;
	
}

bool Date::operator<=(Date input){

	if(years < input.years) return true;
	if(input.years < years) return false;
	if(in_month < input.in_month) return true;
	if(in_month < input.in_month) return false;
	if(day < input.day) return true;
	if(day < input.day) return false;
	if(day == input.day) return true;

}

bool Date::operator>(Date input){

	if(years > input.years) return true;
	if(input.years > years) return false;
	if(in_month > input.in_month) return true;
	if(in_month > input.in_month) return false;
	if(day > input.day) return true;
	if(day > input.day) return false;
	return false;

}

bool Date::operator>=(Date input){

	if(years > input.years) return true;
	if(input.years > years) return false;
	if(in_month > input.in_month) return true;
	if(in_month > input.in_month) return false;
	if(day > input.day) return true;
	if(day > input.day) return false;
	if(day == input.day) return true;

}

 Date Date::operator+(int num){
	if(day + num <= daysInMonth(in_month,years)){
		day = day+ num;
	}
	else{
		int Intcast = in_month + 1;
		if(Intcast>12){
			in_month = Month(Intcast-12);
			years++;
		}
		else in_month = Month(Intcast);
		while(true){
			if(num<daysInMonth(in_month,years)) break;
			if(num>=daysInMonth(in_month,years)) num = num-daysInMonth(in_month,years);
			int Intcast = in_month + 1;
			if(Intcast>12) {
				in_month = Month(Intcast-12);
				years++;
			}
			else in_month = Month(Intcast);

		}
		if(num == 0) {
			Intcast = in_month - 1;
			in_month = Month(Intcast);
			num = daysInMonth(in_month,years);
		}
		day = num;
	}
	return *this;
}
 
 Date Date::operator+=(int num){
	if(day + num <= daysInMonth(in_month,years)){
		day = day+ num;
	}
	else{
		int Intcast = in_month + 1;
		if(Intcast>12){
			in_month = Month(Intcast-12);
			years++;
		}
		else in_month = Month(Intcast);
		while(true){
			if(num<daysInMonth(in_month,years)) break;
			if(num>=daysInMonth(in_month,years)) num = num-daysInMonth(in_month,years);
			int Intcast = in_month + 1;
			if(Intcast>12) {
				in_month = Month(Intcast-12);
				years++;
			}
			else in_month = Month(Intcast);

		}
		if(num == 0) {
			Intcast = in_month - 1;
			in_month = Month(Intcast);
			num = daysInMonth(in_month,years);
		}
		day = num;
	}
	return *this;
}

 Date Date::operator-(int num){
	if(day - num > 0){
		day = day - num;
	}
	else{
		num = num-day;
		int Intcast = in_month - 1;
		if(Intcast<1){
			in_month = Month(12+Intcast);
			years--;
		}
		else in_month = Month(Intcast);

		while(true){
			if(num<daysInMonth(in_month,years)) break;
			if(num>=daysInMonth(in_month,years)) num = num-daysInMonth(in_month,years);
			Intcast = in_month - 1;
			if(Intcast<1) {
				in_month = Month(12+Intcast);
				years--;
			}
			else in_month = Month(Intcast);
		}
		day = daysInMonth(in_month,years) - num;

	}
	return *this;
}

 Date Date::operator-=(int num){
	if(day - num > 0){
		day = day - num;
	}
	else{
		num = num-day;
		int Intcast = in_month - 1;
		if(Intcast<1){
			in_month = Month(12+Intcast);
			years--;
		}
		else in_month = Month(Intcast);

		while(true){
			if(num<daysInMonth(in_month,years)) break;
			if(num>=daysInMonth(in_month,years)) num = num-daysInMonth(in_month,years);
			Intcast = in_month - 1;
			if(Intcast<1) {
				in_month = Month(12+Intcast);
				years--;
			}
			else in_month = Month(Intcast);
		}
		day = daysInMonth(in_month,years) - num;

	}
	return *this;
}

 Date Date::operator++(){
	return *this+1;
}
 
 Date Date::operator--(){
	 return *this-1;
 }

 Date Date::operator++(int){
	Date old = *this;
	*this+1;
	return old;
}

 Date Date::operator--(int){
	 Date old = *this;
	 *this-1;
	 return old;
 }

int Date::operator-(Date input){
	if(in_month == input.in_month && years == input.years){
		int ans = day - input.day;
		return (ans>0?ans:-ans);
	}else{  
		int allday = getTotalDay(*this);
		int in_allday = getTotalDay(input);
		int ans = allday - in_allday;
		return (ans>0?ans:-ans);
	}
}

int Date::getTotalDay(Date obj){
	int total = 0;
	int totalYear = 365 * obj.years;
	for(int i = 0;i < obj.years;i++){
		if(isLeapYear(i)){
			totalYear++;
		}
	}
	int totalMonth = 0;
	Date cast;
	for(int j = 1;j <= int(obj.in_month) ;j++){
		cast.in_month = Month(obj.in_month - j);
		totalMonth += daysInMonth(cast.in_month,obj.years);
	}
	total = totalYear + totalMonth + obj.day ;
	return total;
}