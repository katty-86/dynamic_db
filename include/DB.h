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
	//function for map
	bool findIfTableExist(string tablename);
	bool addTableToDB(Table &table);
	bool deleteTableFromDB(std::string tablename);

public:
	DB();
	~DB();

	/*
	 * Function must be changed adding iterator inside function!!!
	 * */
	bool insert(SQL &s);
	bool select(SQL &s);
	bool deleteRow(SQL &s);
	bool updateRow(SQL &s);
	bool createTable(const std::string &f,
			const std::vector<std::pair<std::string, std::string>> &values);
	bool printTable(const string &tablename);
	//std::string getTableName(const string &tablename)const;
	bool empty(const string &tablename);
	const std::vector<FieldConfig> getFieldConfig(const string &tablename);
	bool writaData(const string &tablename, const std::string &filename);
	std::string readData(const std::string &filename);

};

#endif /* SRC_DB_H_ */
