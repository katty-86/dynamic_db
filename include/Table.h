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
	std::string name;
	std::vector<FieldConfig> vec_config;
	std::list<Record> list_data;

public:
	Table();
	~Table();
	std::string getName() const;
	void setName(const std::string pp);
	void addConfigField(std::string type, std::string name);
	void createTable(const std::string &f,
			std::vector<std::pair<std::string, std::string>> &values);
	void addRow(std::string s);
	void addRow(std::vector<std::pair<std::string, std::string>> expression);
	void describeTable();
	void printTable();
	void read_data(Table &s, std::string filename);
	void save_data(const Table &s, std::string filename);
	std::vector<FieldConfig> getVec_config() const;
	std::list<Record> getList_data() const;
	void clearTable();
	std::list<Record> findMatchingRow(
			std::vector<std::pair<std::string, std::string>> v);
	std::list<std::string> findMatchingRowAccordingExpression(
			std::vector<std::pair<std::string, std::string>> e,
			std::vector<std::pair<std::string, std::string>> v);
	int countMatchingRow(
			const std::vector<std::pair<std::string, std::string>> v);
	bool checkIfListDataEmpty();
	bool checkIfVecConfigEmpty();
	int sizeListData();
	int removeRowFromDB(std::vector<std::pair<std::string, std::string>> v);
	int removeAllFromDB();
	int updateRowFromDB(std::vector<std::pair<std::string, std::string>> update,
			std::vector<std::pair<std::string, std::string>> condition);
	int updateAllFromDB(
			std::vector<std::pair<std::string, std::string>> update);

};

#endif /* SRC_TABLE_H_ */
