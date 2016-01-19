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
#include <algorithm>

class Table {
	std::string name;
	std::vector<FieldConfig> vec_config;
	std::list<Record> list_data;

public:
	Table();
	~Table();
	//Table( Table &&t );
	Table(const Table &t);
	//Table& operator=( Table &&t );

	std::string getName() const;
	void setName(const std::string &pp);
	void addRow(std::string s);
	void addRow(
			const std::vector<std::pair<std::string, std::string>> & expression);
	void addConfigField(const std::string &type, const std::string &name);
	bool describeTable();
	//void printTable();
	const std::vector<FieldConfig> getVec_config() const;
	const std::list<Record> getList_data() const;
	void clearTable();
	std::list<Record> findMatchingRow(
			const std::vector<std::pair<std::string, std::string>> &v);
	std::list<std::string> findMatchingRowAccordingExpression(
			const std::vector<std::pair<std::string, std::string>> &e,
			const std::vector<std::pair<std::string, std::string>> &v);
	int countMatchingRow(
			const std::vector<std::pair<std::string, std::string>> &v);
	bool checkIfListDataEmpty();
	bool checkIfVecConfigEmpty();
	int sizeListData();
	int removeRowFromDB(
			const std::vector<std::pair<std::string, std::string>> &v);
	int removeAllFromDB();
	int updateRowFromDB(
			const std::vector<std::pair<std::string, std::string>> &update,
			const std::vector<std::pair<std::string, std::string>> &condition);
	int updateAllFromDB(
			const std::vector<std::pair<std::string, std::string>> &update);

	bool empty();
	void printData();
};

#endif /* SRC_TABLE_H_ */
