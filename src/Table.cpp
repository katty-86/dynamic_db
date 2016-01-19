/*
 * Table.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "Table.h"
/*
 Table::Table( Table &&t ):name(std::move(t.name)), vec_config(std::move(t.vec_config)),list_data(std::move(t.list_data)) {
 }
 */
Table::Table(const Table &t) :
		name(t.name), vec_config(t.vec_config), list_data(t.list_data) {
}
/*
 Table& Table::operator=( Table &&t ){
 if(this!=&t){
 name=std::move(t.name);
 vec_config=std::move(t.vec_config);
 list_data=std::move(t.list_data);
 t.name.clear();
 t.vec_config.clear();
 t.list_data.clear();
 }
 return *this;
 }
 */
Table::Table() {
	// TODO Auto-generated constructor stub

}

Table::~Table() {
	// TODO Auto-generated destructor stub
}
std::string Table::getName() const {
	return this->name;
}
void Table::setName(const std::string &pp) {

	this->name = pp;
}

void Table::addConfigField(const std::string &type, const std::string &name) {
	std::shared_ptr<FieldConfig> fg = std::make_shared<FieldConfig>(name, type);
	this->vec_config.push_back(*fg);

}

bool Table::empty() {
	if (this->vec_config.empty() == false) {
		return false;
	}
	return true;
}

bool Table::describeTable() {
	if (this->vec_config.empty() == false) {
		std::cout << "*table = \"" << this->name << "\"\n";
		for_each(begin(vec_config), end(vec_config),
				[](FieldConfig &fc) {std::cout <<fc;});
		std::cout << std::endl;
		return true;
	} else {
		std::cout << "Table does not exist " << std::endl;
		return false;
	}

}

void Table::printData() {
	if (this->list_data.empty() == false) {
		for_each(begin(list_data), end(list_data),
				[](const Record &r) {std::cout <<r<<" \n";});
		std::cout << std::endl;
	}
}

void Table::addRow(
		const std::vector<std::pair<std::string, std::string>> &expression) {
	if (this->vec_config.size() == expression.size()) {
		std::shared_ptr<Record> r = std::make_shared<Record>();
		bool resultFlag = r->addRecord(this->vec_config, expression);
		if (resultFlag == true) {
			this->list_data.push_back(*r);
		} else {
			std::cout << "Incorect type of params insert" << std::endl;
		}
	} else {
		std::cout << "Incorect amount of parms in insert" << std::endl;
	}
}

void Table::addRow(std::string s) {
	std::shared_ptr<Record> r = std::make_shared<Record>();
	r->addRecord(this->vec_config, s);
	this->list_data.push_back(*r);
}

const std::vector<FieldConfig> Table::getVec_config() const {
	return this->vec_config;
}

const std::list<Record> Table::getList_data() const {
	return this->list_data;
}

void Table::clearTable() {
	this->vec_config.clear();
	this->list_data.clear();
	this->name = "";
}

std::list<Record> Table::findMatchingRow(
		const std::vector<std::pair<std::string, std::string>> &v) {
	std::string key, value;
	key = v[0].first;
	value = v[0].second;
	std::list<Record> list_result;
	auto ir_rec = std::find_if(begin(vec_config), end(vec_config),
			[&key]( FieldConfig &c) {
				return c.getName()==key;});
	if (ir_rec != vec_config.end()) {
		int pos = std::distance(vec_config.begin(), ir_rec);
		std::copy_if(begin(list_data), begin(list_data),
				std::back_inserter(list_result), [&]( Record &r) {
					return r.compareRecord(value, pos);
				});
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return list_result;
}

int Table::removeRowFromDB(
		const std::vector<std::pair<std::string, std::string>> &v) {
	std::string key, value;
	key = v[0].first;
	value = v[0].second;
	int count = 0;
	auto ir_rec = std::find_if(this->vec_config.begin(), vec_config.end(),
			[&key]( FieldConfig &c) {return c.getName()==key;});
	if (ir_rec != vec_config.end()) {
		int pos = std::distance(vec_config.begin(), ir_rec);
		this->list_data.erase(
				std::remove_if(this->list_data.begin(), this->list_data.end(),
						[&value, &pos]( Record &r) {return r.compareRecord(value, pos);}),
				this->list_data.end());
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return count;
}

int Table::countMatchingRow(
		const std::vector<std::pair<std::string, std::string>> &v) {
	std::string key, value;
	key = v[0].first;
	value = v[0].second;
	int count = 0;
	auto ir_rec = std::find_if(this->vec_config.begin(), vec_config.end(),
			[&key]( FieldConfig &c) {return c.getName()==key;});
	if (ir_rec != vec_config.end()) {
		int pos = std::distance(vec_config.begin(), ir_rec);
		count = count_if(begin(list_data), end(list_data), [&]( Record &r) {
			return r.compareRecord(value, pos);
		});
	} else {
		std::cout << "not correct key" << std::endl;
	}

	return count;
}

int Table::updateRowFromDB(
		const std::vector<std::pair<std::string, std::string>> &update,
		const std::vector<std::pair<std::string, std::string>> &condition) {
	int count = 0;

	std::string update_key = update[0].first;
	std::string update_value = update[0].second;
	std::string condition_key = condition[0].first;
	std::string condition_value = condition[0].second;

	auto it_update =
			std::find_if(this->vec_config.begin(), vec_config.end(),
					[&update_key]( const FieldConfig &c) {return c.getName()==update_key;});
	auto it_condition =
			std::find_if(this->vec_config.begin(), vec_config.end(),
					[&condition_key]( const FieldConfig &c) {return c.getName()==condition_key;});

	if ((it_update != vec_config.end()) && (it_condition != vec_config.end())) {
		int pos_update = std::distance(vec_config.begin(), it_update);
		int pos_condition = std::distance(vec_config.begin(), it_condition);
		for (auto it_list = this->list_data.begin();
				it_list != this->list_data.end(); ++it_list) {
			if (((*it_list).compareRecord(condition_value, pos_condition))
					== true) {
				(*it_list).updateRecord(update_value, pos_update,
						(*it_update).getType());
				count++;
			}

		}
	} else if ((it_update == vec_config.end())
			&& (it_condition != vec_config.end())) {
		std::cout << "Incorrect key in update statement" << std::endl;
	} else if ((it_update != vec_config.end())
			&& (it_condition == vec_config.end())) {
		std::cout << "Incorrect key in condition statement" << std::endl;
	} else {
		std::cout << "Both keys are incorrect" << std::endl;
	}

	return count;
}

int Table::updateAllFromDB(
		const std::vector<std::pair<std::string, std::string>> &update) {
	int count = 0;

	std::string update_key = update[0].first;
	std::string update_value = update[0].second;

	auto it_update =
			std::find_if(begin(vec_config), end(vec_config),
					[&update_key]( const FieldConfig &c) {return c.getName()==update_key;});

	if (it_update != end(vec_config)) {
		int pos_update = std::distance(begin(vec_config), it_update);

		for_each(begin(list_data), end(list_data), [&](Record &r) {
			r.updateRecord(update_value, pos_update,
					(*it_update).getType());
		});

	} else {
		std::cout << "Incorrect key in update statement" << std::endl;
	}

	return count;
}

bool Table::checkIfListDataEmpty() {
	return this->list_data.empty();
}
bool Table::checkIfVecConfigEmpty() {
	return this->vec_config.empty();
}

int Table::sizeListData() {
	return this->list_data.size();
}

int Table::removeAllFromDB() {
	int list_datasize = this->list_data.size();
	this->list_data.clear();
	return list_datasize;
}
/*
 std::list<std::string> Table::findMatchingRowAccordingExpression(
 const std::vector<std::pair<std::string, std::string>> &e,
 const std::vector<std::pair<std::string, std::string>> &v) {
 }*/

