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
#include "Record.h"
#include "FieldConfig.h"
#include <memory>

class Table {
	std::string name_;
	std::vector<FieldConfig> vec_config_;
	std::list<std::shared_ptr<Record>> list_data_;

public:
	Table();
	~Table();
	std::string getName() const;
	void setName(std::string pp);
	void addConfigField(std::string type, std::string name);
	void addRow();
	void describeTable();
	void printTable();

};

#endif /* SRC_TABLE_H_ */
