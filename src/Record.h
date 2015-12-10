/*
 * Record.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef RECORD_H_
#define RECORD_H_
#include <list>
#include "IntegerField.h"
#include "VarcharField.h"
#include "Field.h"
#include "Record.h"

class Record {
	std::list<IntegerField> record_;
	friend std::ostream & operator<<(std::ostream &os, const Record &r);
public:
	Record();
	~Record();
	void addField(Field f);
	bool addField(std::string name, std::string type);
};

#endif /* RECORD_H_ */
