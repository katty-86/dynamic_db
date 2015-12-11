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

class Table {
	std::string name_;
	int fieldCounter_;
	std::vector<FieldConfig> vec_config_;
	std::list<Record> list_data_;
public:
	Table();
	~Table();
	std::string getName() const;
	void setName(std::string pp);
	int getFieldCounter() const;
	void setFieldCounter(int pp);
	void addConfigField(std::string type, std::string name);
	void addRecord();
	void describeTable();

};

#endif /* SRC_TABLE_H_ */
