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
	std::list<Record> findMatchingRow(
			std::vector<std::pair<std::string, std::string>> v);
	std::list<std::string> findMatchingRowAccordingExpression(std::vector<std::pair<std::string, std::string>> e,
				std::vector<std::pair<std::string, std::string>> v);
	int countMatchingRow(std::vector<std::pair<std::string, std::string>> v);
	bool checkIfListDataEmpty();
	bool checkIfVecConfigEmpty();
	int sizeListData();
	int removeRowFromDB(std::vector<std::pair<std::string, std::string>> v);
	int removeAllFromDB();
	int updateRowFromDB(std::vector<std::pair<std::string, std::string>> update,
			std::vector<std::pair<std::string, std::string>> condition);
	int updateAllFromDB(std::vector<std::pair<std::string, std::string>> update);

};

#endif /* SRC_TABLE_H_ */
