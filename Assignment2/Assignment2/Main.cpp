#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include <fstream>
#include "Date.h"
#include "buffer.h"
using namespace std;

map<string,string> file;
string nfile;
static string setcache;

string getStringFromDate(string date){
	return file[date].c_str();
}

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

void loadfile(string filename){
	nfile = filename;
	ifstream openfile(nfile);
	string read;
	while(getline(openfile,read)){
		string date = read.substr(0,8);
		file[date] = read.substr(9,read.size());
	}
	openfile.close();
}

void set(string date){
	for(int i = 0;i<date.size();i++){ // ตัดช่องว่างออก
		if(date[i] == ' ') date.erase(i,1);
	}
	setcache = date; // เอาวันที่ไปเก็บไว้
}

void show(){
	// โชว์ setcache 22 october
	cout << getDate(setcache) << endl;
	cout << file[setcache].c_str() << endl;
}

void cachefile(){
	ifstream openfile("cachefile.txt");
	string read;
	ofstream writefile(nfile);
	while(getline(openfile,read)){
		writefile << read << endl;
	}
	openfile.close();
	remove("cachefile.txt");
}

void savefile(){
	ifstream openfile(nfile);
	string read;
	ofstream writefile("cachefile.txt");
	while(getline(openfile,read)){
		writefile << read.substr(0,8);
		writefile << " ";
		writefile << file[read.substr(0,8)].c_str() << endl;
	}
	openfile.close();
	writefile.close();
	cachefile();
}

void executeCommand(EditorBuffer & buffer, string line) {
	switch (toupper(line[0])) {
	case 'I': for (int i = 1; i < line.length(); i++) {
		buffer.insertCharacter(line[i]);
			  }
			  break;
	case 'D': buffer.deleteCharacter(); break;
	case 'F': buffer.moveCursorForward(); break;
	case 'B': buffer.moveCursorBackward(); break;
	case 'J': buffer.moveCursorToStart(); break;
	case 'E': buffer.moveCursorToEnd(); break;
	case 'Q': break;
	default: cout << "Illegal command" << endl; break;
	}
}

void selectCommand(string command, string data){
	for(int i = 0;i<command.size();i++){
		command[i] = toupper(command[i]);
	}
	if(command == "LOAD"){
		loadfile(data);
	}
	else if(command == "SET"){
		cout << "one" << endl;
		set(data);

	}
	else if(command == "SHOW"){
		show();
	}
	else if(command == "EDIT"){
		EditorBuffer buffer;
		string content = getStringFromDate(setcache);
		for (int i = 0; i < content.length(); i++) {
			buffer.insertCharacter(content[i]);
		}
		buffer.showContents();

		while(true){
			cout << endl;
			cout << "*";
			string com;
			cin >> com;
			if(com[0] == 'Q')break;
			executeCommand(buffer,com);
			file[setcache] = buffer.getContents();
			buffer.showContents();
		}
	}
	else if(command == "SAVE"){
		savefile();
		cout << getDate(setcache) << endl;
		cout << file[setcache] << endl;
	}
	else if(command == "QUIT")exit(0);
}

int main(){
	string line;
	string command = "";
	string data = " ";
	bool hasWS = false;
	cout << "#";
	while(true){
		if(command != "")cout << "#";
		getline(cin,line);

		if(line.length() <= 4){
			command = line.substr(0,4);
			data = " ";
		}else{
			for(int i = 0;i < line.length();i++){
				if(line[i] == ' '){
					hasWS = true;
					command = line.substr(0,i);
					data = line.substr(i+1,line.length()-i);
					break;
				}
			}
		}

		selectCommand(command,data);
	}
}
