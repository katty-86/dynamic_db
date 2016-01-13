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
	shared_ptr<Table> t;
public:
	DB();
	~DB();
	shared_ptr<Table> getTable() const;
	bool saveBDtoFile(string &filename);
	bool readDBfromFile(string &filename);
	void insert( SQL &s);
	void select( SQL &s);
	void deleteRow( SQL &s);
	void updateRow( SQL &s);

};



#endif /* SRC_DB_H_ */
