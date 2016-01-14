/*
 * Record.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include <list>

#include <memory>
#include <vector>
#include <iostream>
#include "Field.h"
#include "FieldConfig.h"
#include "Utils.h"

class Record {
	std::vector<std::shared_ptr<Any_Field>> record_;
	friend std::ostream & operator<<(std::ostream &os, const Record &r);
public:
	Record();
	~Record();
	bool addRecord(const std::vector<FieldConfig> &t, std::string &s);
	bool addRecord(const std::vector<FieldConfig> &t, const std::vector<std::pair<std::string, std::string>> &expression);
	std::vector<std::shared_ptr<Any_Field>> getRecord();
	bool compareRecord(const std::string &value, int distance);
	bool updateRecord(const std::string &value, int distance, DataType dt);
};

