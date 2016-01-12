/*
 * DB.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: kaky
 */

#include "DB.h"



DB::DB() {
	t = make_shared<Table>();
}

DB::~DB() {
	// TODO Auto-generated destructor stub
}

shared_ptr<Table> DB::getTable(){
	return this->t;
}

void DB::createTable() {

	int n;
	string name;
	if(t->getName()!=""){
		t->clearTable();
	}
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
			cout << "Write type from [" << acceptable_type << "]" << endl;
			cin >> type;
			std::transform(type.begin(), type.end(), type.begin(), ::toupper);
		} while (acceptable_type.find(type) == std::string::npos);
		cout << "Write name: ";
		cin >> name;
		cin.ignore(256, '\n');
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		values.at(i)= pair <string, string>(type, name);
	}
	t->createTable(name,values);
}

void DB::saveBDtoFile() {
	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	cin.ignore(256, '\n');
	Serializer helper;
	helper.writaData( t, filename);
}
void DB::readDBfromFile() {
	t->clearTable();
	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	cin.ignore(256, '\n');
	Serializer helper;
	helper.readData(t, filename);
}

void DB::insert() {
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

void DB::insert( SQL &s) {
	if (t->checkIfVecConfigEmpty() == false){
		t->addRow(s.expression);
	}
}

void DB::select(SQL &s) {

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

void DB::deleteRow( SQL &s) {

	if (s.where_condition.empty() == true) {
		t->removeAllFromDB();
	} else {
		t->removeRowFromDB(s.where_condition);
	}

}

void DB::updateRow( SQL &s) {

	if (s.where_condition.empty() == true) {
		t->updateAllFromDB(s.expression);
	} else {
		t->updateRowFromDB(s.expression, s.where_condition);
	}
}