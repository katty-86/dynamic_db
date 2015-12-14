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

class Record {
	std::list<std::shared_ptr<Any_Field>> record_;
	friend std::ostream & operator<<(std::ostream &os, const Record &r);
public:
	Record();
	~Record();
	void addRecord(std::vector <FieldConfig> &t);
};


