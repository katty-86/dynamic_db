/*
 * Record.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef RECORD_H_
#define RECORD_H_
#include <list>
#include "Field.h"
#include "Record.h"

template <class T>
class Record {
	std::list<Field<T>> record_;
	//Field<int> t;
	friend std::ostream & operator<<(std::ostream &os, const Record &r);
public:
	Record();
	~Record();
	//void addField(Field<T> f){record_.push_back(f)};
	//void addRecord(std::string name, std::string type);
};

#endif /* RECORD_H_ */
