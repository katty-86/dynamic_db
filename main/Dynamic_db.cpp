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
#include "Utils.h"
#include "DB.h"
using namespace std;

void displayManu();


int main() {

	string choose;
	shared_ptr<DB> db = make_shared<DB>();
	displayManu();
	do {
		cout << "\n >";
		getline(cin, choose);
		if (choose == "b") {
			db->createTable();
		} else if (choose == "c") {
			db->saveBDtoFile();
			(db->getTable())->printTable();
		} else if (choose == "d") {
			db->readDBfromFile();
			(db->getTable())->printTable();
		} else if (choose == "h") {
			displayManu();
		} else if (choose == "f") {
			(db->getTable())->describeTable();
		} else if (choose == "i") {
			db->insert();
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
	cout << "q- quit\n";
	cout << "h- print help\n";
	cout << "\n\n or write dml statement for existing table \n";
}


