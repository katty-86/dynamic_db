//============================================================================
// Name        : Dynamic_db.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <memory>
#include "Table.h"
#include "SQL.h"
#include <algorithm>
#include <regex>
#include <map>
#include "Utils.h"
#include "DB.h"
using namespace std;

void displayManu();
void createTable(DB &db);
string getNameOfFile();
void insert(DB &db);



std::map<string, DataType> acceptable_type {
	{"INT", DataType::INT},
	{"VAR", DataType::VAR},
	{"FLOAT", DataType::FLOAT},
	{"TIME", DataType::TIME},
	{"UNKNOWN", DataType::UNKNOWN},
};

int main() {

	string choose;
	shared_ptr<DB> db = make_shared<DB>();
	displayManu();
	do {
		cout << "\n >";
		getline(cin, choose);
		if (choose == "b") {
			createTable(*db);
		} else if (choose == "c") {
			string fn=getNameOfFile();
			db->saveBDtoFile(fn);
			(db->getTable())->printTable();
		} else if (choose == "d") {
			string fn=getNameOfFile();
			db->readDBfromFile(fn);
			(db->getTable())->printTable();
		} else if (choose == "h") {
			displayManu();
		} else if (choose == "f") {
			(db->getTable())->describeTable();
		} else if (choose == "i") {
			insert(*db);
		} else if (choose == "q") {
			cout<<"QUIT"<<endl;
		} else {
			if (!(db->getTable())->checkIfListDataEmpty()) {
				SQL sql;
				if(sql.readSQL(choose, (db->getTable())->getName())==true){
					if (sql.statement == 'I') {
						sql.printAll();
						db->insert(sql);
					} else if (sql.statement == 'S') {
						//sql.printAll();
						db->select(sql);
					} else if (sql.statement == 'D') {
						sql.printAll();
						db->deleteRow( sql);
					} else if (sql.statement == 'U') {
						sql.printAll();
						db->updateRow(sql);
					}
				}
				else {
					cout << "Main: unsupported operation" << endl;
				}
			} else {
				cout << "Main: list is empty -task is not possible" << endl;
			}

		}
	} while (choose != "q");

//printing table

	return 0;
}

void displayManu() {
	cout << "b- create db \n";
	cout << "c- commit db\n";
	cout << "d- load db\n";
	cout << "f- describe table\n";
	cout << "e- write dml statement (select, update.....)\n";
	cout << "i -insert data\n";
	cout << "q- quit\n";
	cout << "h- print help\n";
	cout << "\n\n or write dml statement for existing table \n";
}


void createTable(DB &db) {

	int n;
	string name;

	cout << "Set name of table" << endl;
	cin >> name;
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	cout << "how many field do you want to store in table" << endl;
	cin >> n;
	cout << "creating tables...." << endl;
	std::vector<std::pair <std::string, std::string>> values(n);
	for (int i = 0; i < n; i++) {
		//checking function for type
		string name, type;
		do {
			cout << "Write type from [INT VAR TIME FLOAT]" << endl;
			cin >> type;
			std::transform(type.begin(), type.end(), type.begin(), ::toupper);
		} while (acceptable_type.find(type) == acceptable_type.end());
		cout << "Write name: ";
		cin >> name;
		cin.ignore(256, '\n');
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		values.at(i)= pair <string, string>(type, name);
	}
	(db.getTable())->createTable(name,values);
}


string getNameOfFile(){
	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	cin.ignore(256, '\n');
	return filename;
}

void insert(DB &db) {
	if ((db.getTable())->checkIfVecConfigEmpty() == false) {
		cout << "How many rows you want to add" << endl;
		int rows;
		cin >> rows;
		cin.ignore(256, '\n');
		vector<std::pair<std::string, std::string>> expression;
		string s_value;
		for (int i = 0; i < rows; ++i) {
				for (auto it = ((db.getTable())->getVec_config()).begin(); it != ((db.getTable())->getVec_config()).end(); ++it) {
					cout<<"Set correct value of "<<(*it).getTypeString()<<" for field [" <<  (*it).getName() << "]: ";
					cin>>s_value;
					std::cin.ignore(256, '\n');
					expression.push_back(std::pair<std::string, std::string>(s_value, ""));
				}
				(db.getTable())->addRow(expression);
		}
		(db.getTable())->printTable();
	} else {
		cout << "Create table before inserting sth" << endl;
	}
}
