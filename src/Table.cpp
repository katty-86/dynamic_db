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
	if (this->vec_config_.empty() == false) {
		std::cout << "*table = \"" << this->name_ << "\"\n";
		for (auto it = this->vec_config_.begin(); it != this->vec_config_.end();
				++it) {
			std::cout << "" << *it << "\n";
		}
		std::cout << std::endl;
	} else {
		std::cout << "error" << std::endl;
	}

}

void Table::printTable() {
	if (this->vec_config_.empty() == false) {
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
	} else {
		std::cout << "error" << std::endl;
	}

}

void Table::addRow(std::vector<std::pair<std::string, std::string>> expression) {
	if(this->vec_config_.size()==expression.size()){
		std::shared_ptr<Record> r = std::make_shared<Record>();
			bool resultFlag =r->addRecord(this->vec_config_, expression);
			if(resultFlag==true){
				this->list_data_.push_back(*r);
			}
			else{
				std::cout<<"Incorect type of params insert"<<std::endl;
			}
	}
	else{
		std::cout<<"Incorect amount of parms in insert"<<std::endl;
	}
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

std::list<Record> Table::findMatchingRow(
		std::vector<std::pair<std::string, std::string>> v) {
	std::string key, value;
	key = v[0].first;
	value = v[0].second;
	std::list<Record> list_result;
	auto ir_rec = std::find_if(this->vec_config_.begin(), vec_config_.end(),
			[&key]( FieldConfig &c) {return c.getName()==key;});
	if (ir_rec != vec_config_.end()) {
		int pos = std::distance(vec_config_.begin(), ir_rec);
		for (auto it_list = this->list_data_.begin();
				it_list != this->list_data_.end(); ++it_list) {

			if (((*it_list).compareRecord(value, pos)) == true) {
				list_result.push_back(*it_list);
			}

		}
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return list_result;
}

int Table::removeRowFromDB(std::vector<std::pair<std::string, std::string>> v) {
	std::string key, value;
	key = v[0].first;
	value = v[0].second;
	int count = 0;
	auto ir_rec = std::find_if(this->vec_config_.begin(), vec_config_.end(),
			[&key]( FieldConfig &c) {return c.getName()==key;});
	if (ir_rec != vec_config_.end()) {
		int pos = std::distance(vec_config_.begin(), ir_rec);
		this->list_data_.erase(
				std::remove_if(this->list_data_.begin(), this->list_data_.end(),
						[&value, &pos](Record &r) {return r.compareRecord(value, pos);}),
				this->list_data_.end());
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return count;
}

int Table::countMatchingRow(
		std::vector<std::pair<std::string, std::string>> v) {
	std::string key, value;
	key = v[0].first;
	value = v[0].second;

	int count = 0;
	auto ir_rec = std::find_if(this->vec_config_.begin(), vec_config_.end(),
			[&key]( FieldConfig &c) {return c.getName()==key;});
	if (ir_rec != vec_config_.end()) {
		int pos = std::distance(vec_config_.begin(), ir_rec);
		for (auto it_list = this->list_data_.begin();
				it_list != this->list_data_.end(); ++it_list) {
			if (((*it_list).compareRecord(value, pos)) == true) {
				count++;
			}

		}
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return count;
}

int Table::updateRowFromDB(
		std::vector<std::pair<std::string, std::string>> update,
		std::vector<std::pair<std::string, std::string>> condition) {
	int count = 0;

	std::string update_key = update[0].first;
	std::string update_value = update[0].second;
	std::string condition_key = condition[0].first;
	std::string condition_value = condition[0].second;

	auto it_update = std::find_if(this->vec_config_.begin(), vec_config_.end(),
			[&update_key]( FieldConfig &c) {return c.getName()==update_key;});
	auto it_condition =
			std::find_if(this->vec_config_.begin(), vec_config_.end(),
					[&condition_key]( FieldConfig &c) {return c.getName()==condition_key;});

	if ((it_update != vec_config_.end())
			&& (it_condition != vec_config_.end())) {
		int pos_update = std::distance(vec_config_.begin(), it_update);
		int pos_condition = std::distance(vec_config_.begin(), it_condition);
	//	std::cout << "tutaj" << std::endl;
		for (auto it_list = this->list_data_.begin();
				it_list != this->list_data_.end(); ++it_list) {
			if (((*it_list).compareRecord(condition_value, pos_condition))
					== true) {
			//	std::cout << "tutaj!" << std::endl;
				(*it_list).updateRecord(update_value, pos_update,
						(*it_update).getType());
			///	std::cout << "\n->" << *it_list << "\n";
				count++;
			}

		}
	} else if ((it_update == vec_config_.end())
			&& (it_condition != vec_config_.end())) {
		std::cout << "Incorrect key in update statement" << std::endl;
	} else if ((it_update != vec_config_.end())
			&& (it_condition == vec_config_.end())) {
		std::cout << "Incorrect key in condition statement" << std::endl;
	} else {
		std::cout << "Both keys are incorrect" << std::endl;
	}

	return count;
}

int Table::updateAllFromDB(
		std::vector<std::pair<std::string, std::string>> update) {
	int count = 0;

	std::string update_key = update[0].first;
	std::string update_value = update[0].second;

	auto it_update = std::find_if(this->vec_config_.begin(), vec_config_.end(),
			[&update_key]( FieldConfig &c) {return c.getName()==update_key;});

	if (it_update != vec_config_.end()) {
		int pos_update = std::distance(vec_config_.begin(), it_update);
		//std::cout << "tutaj" << std::endl;
		for (auto it_list = this->list_data_.begin();
				it_list != this->list_data_.end(); ++it_list) {
			//std::cout << "tutaj!" << std::endl;
			(*it_list).updateRecord(update_value, pos_update,
					(*it_update).getType());
			//std::cout << "\n->" << *it_list << "\n";
			count++;

		}
	} else {
		std::cout << "Incorrect key in update statement" << std::endl;
	}

	return count;
}

bool Table::checkIfListDataEmpty() {
	return this->list_data_.empty();
}
bool Table::checkIfVecConfigEmpty() {
	return this->vec_config_.empty();
}

int Table::sizeListData() {
	return this->list_data_.size();
}

int Table::removeAllFromDB() {
	int list_data_size = this->list_data_.size();
	this->list_data_.clear();
	return list_data_size;
}
std::list<std::string> Table::findMatchingRowAccordingExpression(
		std::vector<std::pair<std::string, std::string>> e,
		std::vector<std::pair<std::string, std::string>> v) {}


