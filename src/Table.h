/*
 * Table.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef SRC_TABLE_H_
#define SRC_TABLE_H_
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "Record.h"
#include "FieldConfig.h"
#include <memory>
#include <iterator>

class Table {
	std::string name_;
	std::vector<FieldConfig> vec_config_;
	std::list<Record> list_data_;

public:
	Table();
	~Table();
	std::string getName() const;
	void setName(std::string pp);
	void addConfigField(std::string type, std::string name);
	void addRow();
	void addRow(std::string s);
	void describeTable();
	void printTable();
	void read_data(Table &s, std::string filename);
	void save_data(const Table &s, std::string filename);
	std::vector<FieldConfig> getVec_config();
	std::list<Record> getList_data();
	std::string getName();
	void clearTable();
	//select * from nazwa_tabeli where
	std::list<Record> findMatchingRow(std::string key,
			std::string value);
	int countMatchingRow(std::string key,
			std::string value);
	bool checkIfListDataEmpty();
	bool checkIfVecConfigEmpty();

};

#endif /* SRC_TABLE_H_ */
