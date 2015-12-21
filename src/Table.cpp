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

void Table::addConfigField(std::string type, std::string name) {

	std::shared_ptr<FieldConfig> fg = std::make_shared<FieldConfig>(name, type);
	this->vec_config_.push_back(*fg);

}

void Table::describeTable() {
	std::cout << "*table = \"" << this->name_ << "\"\n";
	for (auto it = this->vec_config_.begin(); it != this->vec_config_.end();
			++it) {
		std::cout << "" << *it << "\n";
	}
	std::cout << std::endl;
}

void Table::printTable() {
	std::cout << "*table = \"" << this->name_ << "\"\n";
	for (auto it = this->vec_config_.begin(); it != this->vec_config_.end();
			++it) {
		std::cout << "" << *it << " ";
	}
	std::cout << "\n";
	for (auto it = this->list_data_.begin(); it != this->list_data_.end();
			++it) {
		std::cout << "" << *it << "\n";
	}
	std::cout << std::endl;
}

void Table::addRow() {
	std::shared_ptr<Record> r = std::make_shared<Record>();
	r->addRecord(this->vec_config_);
	this->list_data_.push_back(*r);

}

void Table::addRow(std::string s) {
	std::shared_ptr<Record> r = std::make_shared<Record>();
	r->addRecord(this->vec_config_, s);
	this->list_data_.push_back(*r);
}

std::vector<FieldConfig> Table::getVec_config() {
	return this->vec_config_;
}

std::string Table::getName() {
	return this->name_;
}

std::list<Record> Table::getList_data() {
	return this->list_data_;
}

void Table::clearTable() {
	this->vec_config_.clear();
	this->list_data_.clear();
	this->name_ = "";
}

std::list<Record> Table::findMatchingRow(std::string key,
		std::string value) {
	std::transform(key.begin(), key.end(), key.begin(), ::toupper);
	std::transform(value.begin(), value.end(), value.begin(), ::toupper);
	std::list<Record> list_result;
	auto ir_rec = std::find_if(this->vec_config_.begin(), vec_config_.end(),
			[&key]( FieldConfig &c) {return c.getName()==key;});
	if (ir_rec != vec_config_.end()) {
		int pos = std::distance(vec_config_.begin(), ir_rec);
		for (auto it_list = this->list_data_.begin(); it_list != this->list_data_.end();
				++it_list) {
			if(((*it_list).compareRecord(value,  pos))==true){
				list_result.push_back(*it_list);
			}

		}
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return list_result;
}

int Table::countMatchingRow(std::string key,
		std::string value){
	std::transform(key.begin(), key.end(), key.begin(), ::toupper);
	std::transform(value.begin(), value.end(), value.begin(), ::toupper);
	int count=0;
	auto ir_rec = std::find_if(this->vec_config_.begin(), vec_config_.end(),
			[&key]( FieldConfig &c) {return c.getName()==key;});
	if (ir_rec != vec_config_.end()) {
		int pos = std::distance(vec_config_.begin(), ir_rec);
		for (auto it_list = this->list_data_.begin(); it_list != this->list_data_.end();
				++it_list) {
			if(((*it_list).compareRecord(value,  pos))==true){
				count++;
			}

		}
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return count;
}
bool Table::checkIfListDataEmpty() {
	return this->list_data_.empty();
}
bool Table::checkIfVecConfigEmpty() {
	return this->vec_config_.empty();
}

