/*
 * Record.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */
#include <memory>
#include "Record.h"

Record::Record() {
	// TODO Auto-generated constructor stub

}

Record::~Record() {
	// TODO Auto-generated destructor stub
}

void Record::addRecord(std::vector<FieldConfig> &t) {

	for (auto it = t.begin(); it != t.end(); ++it) {
		std::cout << *it << std::endl;
		if ((*it).getType() == Data_type::INT) {
			int value;
			std::cin >> value;
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<int>>(value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::VAR) {
			std::string value;
			std::cin >> value;
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<std::string>>(value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::FLOAT) {
			float value;
			std::cin >> value;
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<float>>(value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::TIME) {
			long value;
			std::cin >> value;
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<long>>(value);
			this->record_.push_back(tmp);
		} else {

		}
	}
}

std::ostream & operator<<(std::ostream &os, const Record &r){

	for(auto it=r.record_.begin(); it!=r.record_.end(); ++it){
		os << "" << (**it).getValueString() << " ";
	}
	return os;
}


