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

	//Record r;
	std::shared_ptr<Record> r = std::make_shared<Record>();
	r->addRecord(this->vec_config_);
	this->list_data_.push_back(*r);

}


void Table::addRow(std::string s){
	//Record r;
		std::shared_ptr<Record> r = std::make_shared<Record>();
		r->addRecord(this->vec_config_, s);
		this->list_data_.push_back(*r);
}
/*void Table::save_data(const Table &s, std::string filename) {
 std::ofstream ofs(filename.c_str());
 boost::archive::text_oarchive oa(ofs);
 oa << s;
 }

 void Table::read_data(Table &s, std::string filename) {

 std::ifstream ifs(filename.c_str());
 boost::archive::text_iarchive ia(ifs);
 ia >> s;
 }*/

std::vector<FieldConfig> Table::getVec_config() {
	return this->vec_config_;
}

std::string Table::getName() {
	return this->name_;
}

std::list<Record> Table::getList_data() {
	return this->list_data_;
}



void Table::clearTable(){
	this->vec_config_.clear();
	this->list_data_.clear();
	this->name_="";
}

