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
//#include "Field.h"
//#include "Record.h"
#include "Table.h"

using namespace std;
//
//struct Table_config_t {
//	std::string name;
//	int count;
//};
//
//struct Row_config_t {
//	std::string name;
//	std::string type;
//};
void displayManu();
void DMLMenu();
void createTable(shared_ptr<Table> &t);

int main() {

	char choose;
	shared_ptr<Table> t = make_shared<Table>();
	do {
		displayManu();
		cin >> choose;
		if (choose == 'b') {
			createTable(t);

		} else if (choose == 'c') {

		} else if (choose == 'g') {

		} else if (choose == 'e') {
			DMLMenu();
			if (choose == 'i') {
				cout << "How many rows you want to add" << endl;
				int rows;
				cin >> rows;
				for (int i = 0; i < rows; ++i) {
					t->addRow();
				}
				t->printTable();
			} else if (choose == 's') {

			} else {

			}

		} else if (choose == 'f') {
			t->describeTable();
		} else {

		}
	} while (choose != 'q');

//printing table

	return 0;
}

void displayManu() {
	cout << "what you want to do?\n";
	cout << "config_db_file - config db_file \n";
	cout << "b- create db \n";
	cout << "c- commit db\n";
	cout << "d- load db\n";
	cout << "f- describe table\n";
	cout << "e- write dml statement (select, update.....)\n";
	cout << "q- quit\n";
	cout << ">";
}

void DMLMenu() {
	cout << "i- insert \n";
	cout << "d- delete\n";
	cout << "u- update\n";
	cout << "s- select\n";
	cout << ">";
}

void createTable(shared_ptr<Table> &t){

	int n;
			string name;
			cout << "Set name of table" << endl;
			cin >> name;
			t->setName(name);
			cout << "how many field do you want to store in table" << endl;
			cin >> n;
			cout << "creating tables...." << endl;
			for (int i = 0; i < n; i++) {
				//checking function for type
				string name, type;
				cout << "type(VAR, INT, FLOAT, TIME): ";
				cin >> type;
				cout << "name: ";
				cin >> name;
				t->addConfigField(type, name);
			}
}

