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
#include "Serializer.h"
#include <algorithm>
using namespace std;

void displayManu();
void DMLMenu();
void createTable(shared_ptr<Table> &t);
const std::string acceptable_type = ("INT VAR TIME FLOAT");

int main() {

	char choose;
	shared_ptr<Table> t = make_shared<Table>();
	do {
		displayManu();
		cin >> choose;
		if (choose == 'b') {
			createTable(t);

		} else if (choose == 'c') {
			string filename;
			cout << "Set name of the file" << endl;
			cin >> filename;
			Serializer helper;
			helper.writaData(t, filename);

		} else if (choose == 'd') {
			t->clearTable();
			string filename;
			cout << "Set name of the file" << endl;
			cin >> filename;
			Serializer helper;
			helper.readData(t, filename);

		} else if (choose == 'e') {
			DMLMenu();
			cin >> choose;
			if (choose == 'i') {
				cout << "How many rows you want to add" << endl;
				int rows;
				cin >> rows;
				for (int i = 0; i < rows; ++i) {
					t->addRow();
				}
				t->printTable();
			} else if (choose == 's') {
				t->printTable();
			} else if (choose == 'd') {
				t->findRow("NAZWISKO", "krzys");
			} else if (choose == 'u') {
				t->findRow("imieiiii", "krzys");
			}

			else {

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

void createTable(shared_ptr<Table> &t) {

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
		do {
			cout << "Write type from [" << acceptable_type << "]" << endl;
			cin >> type;
			std::transform(type.begin(), type.end(), type.begin(), ::toupper);
		} while (acceptable_type.find(type) == std::string::npos);

		cout << "Write name: ";
		cin >> name;
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		t->addConfigField(type, name);
	}
}

