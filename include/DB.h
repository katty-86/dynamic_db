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
#include <map>
#include "Table.h"
#include "SQL.h"
using namespace std;


class DB {
	//Todo only for one table -> change to map  map<string, Table> db
	std::map<std::string, shared_ptr<Table>> tables;
	shared_ptr<Table> t;
public:
	DB();
	~DB();
//	bool saveBDtoFile(const string &filename);
//	bool readDBfromFile(const string &filename);
	void insert( SQL &s);
	void select( SQL &s);
	void deleteRow( SQL &s);
	void updateRow( SQL &s);
	void createTable(const std::string &f, const std::vector<std::pair <std::string, std::string>> &values);
	void printTable();
	std::string getTableName()const;
	bool empty();
	const std::vector<FieldConfig> getFieldConfig();
	bool writaData( const std::string &filename);
	bool readData(const std::string &filename);


};



#endif /* SRC_DB_H_ */
