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
	void addRecord(std::vector<FieldConfig> &t);
	bool addRecord(std::vector<FieldConfig> &t, std::string s);
	bool addRecord(std::vector<FieldConfig> &t, std::vector<std::pair<std::string, std::string>> expression);
	std::vector<std::shared_ptr<Any_Field>> getRecord();
	bool compareRecord(std::string value, int distance);
	bool updateRecord(std::string value, int distance, Data_type dt);
};

