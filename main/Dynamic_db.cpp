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
void insert(DB &db, string s);
string getNameOfFile(char fileAccess);

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
			cout << "Save table to file\n";
			cout << "What table do you want to save" << endl;
			string tablename;
			cin >> tablename;
			cin.ignore(256, '\n');
			string fn = getNameOfFile('w');
			if (!fn.empty()) {
				cout
						<< (db->writaData(tablename, fn) ?
								"Writing ok" : "Writing not ok") << endl;
			}
		} else if (choose == "d") {
			cout << "Read table from file" << endl;
			string fn = getNameOfFile('r');
			if (!fn.empty()) {
				string tablename = db->readData(fn);
				if (tablename != "") {
					cout << "Reading ok" << endl;
					db->printTable(tablename);
				} else {
					cout << "Reading not ok" << endl;
				}

			}
		} else if (choose == "h") {
			displayManu();
		} else if (choose == "f") {
			cout << "Describe table" << endl;
			cout << "What table do you want to describe" << endl;
			string tablename;
			db->printTable(tablename);
		} else if (choose == "i") {
			cout << "Insert data to table" << endl;
			cout << "Write name of table" << endl;
			string tablename;
			cin >> tablename;
			cin.ignore(256, '\n');
			insert(*db, tablename);
		} else if (choose == "q") {
			cout << "QUIT" << endl;
		} else {
			//if (!db->empty()) {
			SQL sql;
			if (sql.readSQL(choose) == true) {
				sql.printAll();
				if (sql.statement == 'I') {
					sql.printAll();
					db->insert(sql);
				} else if (sql.statement == 'S') {
					//sql.printAll();
					db->select(sql);
				} else if (sql.statement == 'D') {
					sql.printAll();
					db->deleteRow(sql);
				} else if (sql.statement == 'U') {
					sql.printAll();
					db->updateRow(sql);
				}
			} else {
				cout << "Main: unsupported operation" << endl;
			}
			/*} else {
			 cout << "Main: list is empty -task is not possible" << endl;
			 }*/

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
	n = readIntger("");
	cout << "creating tables...." << endl;
	std::vector<std::pair<std::string, std::string>> values(n);
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
		values.at(i) = pair<string, string>(type, name);
	}
	db.createTable(name, values);
}

string getNameOfFile(char fileAccess) {

	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	cin.ignore(256, '\n');
	file_status status = getStatusOfFile(filename);
	cout << "File name verification.." << endl;
	if (((fileAccess == 'w')
			&& ((status == file_status::NOT_EXIST)
					|| (status == file_status::EXIST_AND_EMPTY)))
			|| ((fileAccess == 'r') && (status == file_status::EXIST_NOT_EMPTY))) {
		cout << "File name ok" << endl;
	} else {
		cout << "Incorrect file" << endl;
		filename.clear();
	}
	return filename;
}
/*
 * Adding verification
 * */
void insert(DB &db, string str) {
	if (db.empty(str) == false) {
		cout << "How many rows you want to add" << endl;
		int rows;
		cin >> rows;
		cin.ignore(256, '\n');
		vector<std::pair<std::string, std::string>> expression;
		std::vector<FieldConfig> vec_config = db.getFieldConfig(str);
		string s_value;
		for (int i = 0; i < rows; ++i) {
			SQL s { 'I', 0, 0, str };
			for (auto it = begin(vec_config); it != end(vec_config); ++it) {
				do {
					cout << "Set correct value of " << (*it).getTypeString()
							<< " for field [" << (*it).getName() << "]: ";
					cin >> s_value;
					std::cin.ignore(256, '\n');
				} while (!verifyStringIsCorrectType((*it).getTypeString(),
						s_value));
				s.expression.push_back(
						std::pair<std::string, std::string>(s_value, ""));
			}
			db.insert(s);
		}
		db.printTable(str);
	} else {
		cout << "Create table before inserting sth" << endl;
	}
}
