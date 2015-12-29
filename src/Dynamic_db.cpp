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
#include "SQL.h"
#include <algorithm>
#include <regex>
#include "Utils.h"
using namespace std;

void displayManu();
void createTable(shared_ptr<Table> &t);
void saveBDtoFile(shared_ptr<Table> &t);
void readDBfromFile(shared_ptr<Table> &t);
void insert(shared_ptr<Table> &t);
void insert(shared_ptr<Table> &t, SQL &s);
void select(shared_ptr<Table> &t, SQL &s);
void deleteRow(shared_ptr<Table> &t, SQL &s);
void updateRow(shared_ptr<Table> &t, SQL &s);
string acceptable_type = ("INT VAR TIME FLOAT");

int main() {

	string choose;
	shared_ptr<Table> t = make_shared<Table>();
	displayManu();
	do {
		cout << "\n >";
		//cin.ignore(256, '\n');
		getline(cin, choose);
		//	cin >> choose;
		if (choose == "b") {
			createTable(t);
		} else if (choose == "c") {
			saveBDtoFile(t);
			t->printTable();
		} else if (choose == "d") {
			readDBfromFile(t);
			t->printTable();
		} else if (choose == "h") {
			displayManu();
		} else if (choose == "f") {
			t->describeTable();
		} else if (choose == "i") {
			insert(t);
		} else if (choose == "q") {
			cout<<"QUIT"<<endl;
		} else {
			if (!t->checkIfListDataEmpty()) {
				SQL sql;
				if(sql.readSQL(choose, t->getName())==true){
					if (sql.statement == 'I') {
						sql.printAll();
						insert(t, sql);
					} else if (sql.statement == 'S') {
						//sql.printAll();
						select(t, sql);
					} else if (sql.statement == 'D') {
						sql.printAll();
						deleteRow(t, sql);
					} else if (sql.statement == 'U') {
						sql.printAll();
						updateRow(t, sql);
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
	cout << "q- quit\n";
	cout << "h- print help\n";
	cout << "\n\n or write dml statement for existing table \n";
}

void createTable(shared_ptr<Table> &t) {

	int n;
	string name;
	cout << "Set name of table" << endl;
	cin >> name;
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
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
		cin.ignore(256, '\n');
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		t->addConfigField(type, name);
	}
}

void saveBDtoFile(shared_ptr<Table> &t) {
	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	cin.ignore(256, '\n');
	Serializer helper;
	helper.writaData(t, filename);
}
void readDBfromFile(shared_ptr<Table> &t) {
	t->clearTable();
	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	cin.ignore(256, '\n');
	Serializer helper;
	helper.readData(t, filename);
}

void insert(shared_ptr<Table> &t) {
	if (t->checkIfVecConfigEmpty() == false) {
		cout << "How many rows you want to add" << endl;
		int rows;
		cin >> rows;
		cin.ignore(256, '\n');
		for (int i = 0; i < rows; ++i) {
			t->addRow();
		}
		t->printTable();
	} else {
		cout << "Create table before inserting sth" << endl;
	}
}

void insert(shared_ptr<Table> &t, SQL &s) {
}

void select(shared_ptr<Table> &t, SQL &s) {

	if (s.flag_all == true) {
		if (s.where_condition.empty() == true) {
			t->printTable();
		} else {
			list<Record> lis_result = t->findMatchingRow(s.where_condition);
			for (auto i = lis_result.begin(); i != lis_result.end(); ++i) {
				cout << *i << endl;
			}
		}

	} else if (s.flag_count == true) {
		if (s.where_condition.empty() == true) {
			cout << t->sizeListData() << endl;
		} else {
			cout << t->countMatchingRow(s.where_condition) << endl;
		}
	} else {
		cout << "not supported:)" << endl;
		//cout<<t->findMatchingRowAccordingExpression(s.expression, s.where_condition);
		//TODO check if param is ok
		//specify column which can be printed
	}

}

void deleteRow(shared_ptr<Table> &t, SQL &s) {

	if (s.where_condition.empty() == true) {
		t->removeAllFromDB();
	} else {
		t->removeRowFromDB(s.where_condition);
	}

}

void updateRow(shared_ptr<Table> &t, SQL &s) {

	if (s.where_condition.empty() == true) {
		t->updateAllFromDB(s.expression);
	} else {
		t->updateRowFromDB(s.expression, s.where_condition);
	}
}
