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
#include "Record.h"
#include "FieldConfig.h"

class Table {
	std::string name_;
	int fieldCounter_;
	std::vector<FieldConfig> table_config;
	std::vector<Record> data_;
public:
	Table();
	~Table();
	std::string getName() const;
	void setName(std::string pp);
	int getFieldCounter() const;
	void setFieldCounter(int pp);
};

#endif /* SRC_TABLE_H_ */
