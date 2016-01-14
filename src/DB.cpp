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

shared_ptr<Table> DB::getTable() const {
	return this->t;
}

bool DB::saveBDtoFile(const string &filename) {
	Serializer helper;
	return helper.writaData( t, filename);
}
bool DB::readDBfromFile(const string &filename) {
	t->clearTable();
	Serializer helper;
	return helper.readData(t, filename);
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
