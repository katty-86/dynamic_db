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
#include <boost/serialization/list.hpp>
//#include <boost/serialization/shared_ptr.hpp>
//#include <boost/serialization/utility.hpp>
#include <boost/serialization/serialization.hpp>
#include "Field.h"
#include "FieldConfig.h"

class Record {
	std::list<std::shared_ptr<Any_Field>> record_;
	friend std::ostream & operator<<(std::ostream &os, const Record &r);
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		//ar.register_type(static_cast< *>(NULL));
		ar &record_;

	}
public:
	Record();
	~Record();
	void addRecord(std::vector<FieldConfig> &t);
};

