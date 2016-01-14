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
	void addConfigField(const std::string &type, const std::string &name);

public:
	Table();
	~Table();
	std::string getName() const;
	void setName(const std::string &pp);
	void createTable(const std::string &f, const std::vector<std::pair <std::string, std::string>> &values);
	void addRow(std::string s);
	void addRow(const std::vector<std::pair<std::string, std::string>> & expression);
	void describeTable();
	void printTable();
	void read_data(const Table &s, const std::string &filename);
	void save_data(const Table &s, const  std::string &filename);
	std::vector<FieldConfig> getVec_config() const;
	std::list<Record> getList_data()const ;
	void clearTable();
	std::list<Record> findMatchingRow(const
			std::vector<std::pair<std::string, std::string>> &v);
	std::list<std::string> findMatchingRowAccordingExpression(const std::vector<std::pair<std::string, std::string>> &e,
				const std::vector<std::pair<std::string, std::string>> &v);
	int countMatchingRow(const std::vector<std::pair<std::string, std::string>> &v);
	bool checkIfListDataEmpty();
	bool checkIfVecConfigEmpty();
	int sizeListData();
	int removeRowFromDB(const std::vector<std::pair<std::string, std::string>> &v);
	int removeAllFromDB();
	int updateRowFromDB(const std::vector<std::pair<std::string, std::string>> &update,
			const std::vector<std::pair<std::string, std::string>> &condition);
	int updateAllFromDB(const std::vector<std::pair<std::string, std::string>> &update);

};

#endif /* SRC_TABLE_H_ */
