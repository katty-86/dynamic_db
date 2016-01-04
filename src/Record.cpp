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
void Record::addRecord(std::vector<FieldConfig> &t) {

	for (auto it = t.begin(); it != t.end(); ++it) {
		if ((*it).getType() == Data_type::INT) {
			int value = readIntger((*it).getName());
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<int>>(
					value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::VAR) {
			std::string value = readString((*it).getName());
			std::shared_ptr<Any_Field> tmp =
					std::make_shared<Field<std::string>>(value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::FLOAT) {
			float value;
			std::cin >> value;
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<float>>(
					value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::TIME) {
			long value;
			std::cin >> value;
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<long>>(
					value);
			this->record_.push_back(tmp);
		} else {

		}
	}
}

bool Record::addRecord(std::vector<FieldConfig> &t, std::vector<std::pair<std::string, std::string>> expression){
	auto it_expression=expression.begin();
	std::cout<<"add record"<<std::endl;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::string s_value= it_expression->first;
		std::cout<<"--"<<s_value<<"--"<<std::endl;
			if ((*it).getType() == Data_type::INT) {
				if(checkIfInt(s_value)==false){
					return false;
				}
				int value = std::atoi(s_value.c_str());
				std::shared_ptr<Any_Field> tmp = std::make_shared<Field<int>>(
						value);
				this->record_.push_back(tmp);
			} else if ((*it).getType() == Data_type::VAR) {
				if(checkIfVar(s_value)==false){
					std::cout<<"what is"<<std::endl;
					return false;
				}
				std::shared_ptr<Any_Field> tmp =
						std::make_shared<Field<std::string>>(s_value);
				this->record_.push_back(tmp);
			} else if ((*it).getType() == Data_type::FLOAT) {
				if(checkIfFloat(s_value)==false){
					return false;
				}
				float value = std::atof(s_value.c_str());
				std::shared_ptr<Any_Field> tmp = std::make_shared<Field<float>>(
						value);
				this->record_.push_back(tmp);
			} else if ((*it).getType() == Data_type::TIME) {
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

void Record::addRecord(std::vector<FieldConfig> &t, std::string s) {

	for (auto it = t.begin(); it != t.end(); ++it) {
		int pos = s.find(";");
		std::string s_value = s.substr(1, pos - 1);
		s.erase(0, pos + 1);
		if ((*it).getType() == Data_type::INT) {
			int value = std::atoi(s_value.c_str());
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<int>>(
					value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::VAR) {
			std::shared_ptr<Any_Field> tmp =
					std::make_shared<Field<std::string>>(s_value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::FLOAT) {
			float value = std::atof(s_value.c_str());
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<float>>(
					value);
			this->record_.push_back(tmp);
		} else if ((*it).getType() == Data_type::TIME) {
			long value = std::atol(s_value.c_str());
			std::shared_ptr<Any_Field> tmp = std::make_shared<Field<long>>(
					value);
			this->record_.push_back(tmp);
		} else {

		}

	}

}

std::ostream & operator<<(std::ostream &os, const Record &r) {

	for (auto it = r.record_.begin(); it != r.record_.end(); ++it) {
		os << " " << (**it).getValueString() << ";";
	}
	return os;
}

bool Record::compareRecord(std::string value, int distance) {
	bool flag = false;
	auto it = this->record_[distance];
	if ((value.compare(it->getValueString())) == 0) {
		flag = true;
	}
	return flag;
}

void Record::updateRecord(std::string s_value, int distance, Data_type dt) {

	auto it = &this->record_[distance];
	if (dt == Data_type::INT) {
		int value = std::atoi(s_value.c_str());
		it->reset(new Field<int>(value));
	} else if (dt == Data_type::VAR) {
		it->reset(new Field<std::string>(s_value));
	} else if (dt == Data_type::FLOAT) {
		float value = std::atof(s_value.c_str());
		it->reset(new Field<float>(value));
	} else if (dt == Data_type::TIME) {
		long value = std::atol(s_value.c_str());
		it->reset(new Field<long>(value));
	} else {

	}
	for (auto it = this->record_.begin(); it != this->record_.end(); ++it) {
		std::cout << "* " << (**it).getValueString() << ";";
	}
}
