/*
 * DB.h
 *
 *  Created on: Jan 11, 2016
 *      Author: kaky
 */

#ifndef SRC_DB_H_
#define SRC_DB_H_
#include <string>
#include <iostream>
#include <memory>
#include "Table.h"
#include "SQL.h"
#include "Serializer.h"
using namespace std;


class DB {
	string acceptable_type = ("INT VAR TIME FLOAT");
	shared_ptr<Table> t;
public:
	DB();
	~DB();
	shared_ptr<Table> getTable();
	void createTable();
	void saveBDtoFile();
	void readDBfromFile();
	void insert();
	void insert( SQL &s);
	void select( SQL &s);
	void deleteRow( SQL &s);
	void updateRow( SQL &s);

};



#endif /* SRC_DB_H_ */
