#include <iostream>
#include "Date.h"
#include <string>
#include <sstream>

using namespace std;

string intToString(int num){
	stringstream stream;
	stream<<num;
	return stream.str();
}


int stringToInt(string num){
	stringstream stream(num);
	int numN;
	stream >> numN;
	return numN;
}
string getDate(string date){
	int in_day = stringToInt(date.substr(0,2));
	string pure_month = date.substr(2,2);
	Month in_month = Month(stringToInt(pure_month));
	int in_year = stringToInt(date.substr(4,4));

	Date object(in_month,in_day,in_year);
	string value = "";
	value += intToString(in_day)+" ";
	value += object.getMonth() + " ";
	value += intToString(in_year);
	return value;
}



/*int main() {
	while(true){
		string input;
		cout << "=" ;
		cin >> input;
		string N = getDate(input);
		cout << "Date : " << N << endl;
	}
}*/

