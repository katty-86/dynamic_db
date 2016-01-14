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

std::vector<std::shared_ptr<Any_Field>> Record::getRecord() {
	return this->record_;
}

bool Record::addRecord(const std::vector<FieldConfig> &t, const std::vector<std::pair<std::string, std::string>> &expression){
	auto it_expression=expression.begin();
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::string s_value= it_expression->first;
			if ((*it).getType() == DataType::INT) {
				if(checkIfInt(s_value)==false){
					return false;
				}
				int value = std::atoi(s_value.c_str());
				std::shared_ptr<Any_Field> tmp = std::make_shared<Field<int>>(
						value);
				this->record_.push_back(tmp);
			} else if ((*it).getType() == DataType::VAR) {
				if(checkIfVar(s_value)==false){
					std::cout<<"what is"<<std::endl;
					return false;
				}
				std::shared_ptr<Any_Field> tmp =
						std::make_shared<Field<std::string>>(s_value);
				this->record_.push_back(tmp);
			} else if ((*it).getType() == DataType::FLOAT) {
				if(checkIfFloat(s_value)==false){
					return false;
				}
				float value = std::atof(s_value.c_str());
				std::shared_ptr<Any_Field> tmp = std::make_shared<Field<float>>(
						value);
				this->record_.push_back(tmp);
			} else if ((*it).getType() == DataType::TIME) {
				long value = std::atol(s_value.c_str());
				std::shared_ptr<Any_Field> tmp = std::make_shared<Field<long>>(
						value);
				this->record_.push_back(tmp);
			} else {

			}
			++it_expression;
		}
	return true;
}

bool Record::addRecord(const std::vector<FieldConfig> &t, std::string &s) {

	for (auto it = t.begin(); it != t.end(); ++it) {
		int pos = s.find(";");
		std::string s_value = s.substr(1, pos - 1);
		s.erase(0, pos + 1);
		if ((*it).getType() == DataType::INT) {
			if(checkIfInt(s_value)==false){
				return false;
			}
			int value = std::atoi(s_value.c_str());
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<int>>(
					value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == DataType::VAR) {
			if(checkIfVar(s_value)==false){
				return false;
			}
			std::shared_ptr<Any_Field> tmp =
					std::make_shared<Field<std::string>>(s_value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == DataType::FLOAT) {
			if(checkIfFloat(s_value)==false){
				return false;
			}
			float value = std::atof(s_value.c_str());
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<float>>(
					value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == DataType::TIME) {
			if(checkIfInt(s_value)==false){
				return false;
			}
			long value = std::atol(s_value.c_str());
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<long>>(
					value);
			this->record_.push_back(tmp);
		} else {
			return false;
		}

	}
	return true;

}

std::ostream & operator<<(std::ostream &os, const Record &r) {

	for (auto it = r.record_.begin(); it != r.record_.end(); ++it) {
		os << " " << (**it).getValueString() << ";";
	}
	return os;
}

bool Record::compareRecord(const std::string &value, int distance) {
	bool flag = false;
	auto it = this->record_[distance];
	if ((value.compare(it->getValueString())) == 0) {
		flag = true;
	}
	return flag;
}

bool Record::updateRecord(const std::string &s_value, int distance, DataType dt) {

	auto it = &this->record_[distance];
	if (dt == DataType::INT) {
		if(checkIfInt(s_value)){
			int value = std::atoi(s_value.c_str());
			it->reset(new Field<int>(value));
		}
		else{
			return false;
		}
	} else if (dt == DataType::VAR) {
			it->reset(new Field<std::string>(s_value));
	} else if (dt == DataType::FLOAT) {
		if(checkIfFloat(s_value)){
			float value = std::atof(s_value.c_str());
			it->reset(new Field<float>(value));
		}
		else{
			return false;
		}
	} else if (dt == DataType::TIME) {
		if(checkIfInt(s_value)){
			long value = std::atol(s_value.c_str());
			it->reset(new Field<long>(value));
		}
		else{
			return false;
		}
	} else {
		return false;
	}
	return true;
}
