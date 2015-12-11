/*
 * Table.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "Table.h"

Table::Table() {
	// TODO Auto-generated constructor stub

}

Table::~Table() {
	// TODO Auto-generated destructor stub
}
std::string Table::getName() const {
	return this->name_;
}
void Table::setName(std::string pp) {

	this->name_ = pp;
}

int Table::getFieldCounter() const {
	return this->fieldCounter_;
}
void Table::setFieldCounter(int pp) {
	this->fieldCounter_ = pp;
}

void Table::addConfigField(std::string type, std::string name) {

	std::shared_ptr<FieldConfig> fg = std::make_shared<FieldConfig>(name, type);
	this->vec_config_.push_back(*fg);

}

void Table::describeTable() {
	std::cout<<"*table = \""<<this->name_<<"\"\n";
	for (auto it = this->vec_config_.begin(); it != this->vec_config_.end();
			++it) {
		std::cout << " " << *it << "\n";
	}
	std::cout<<std::endl;
}
