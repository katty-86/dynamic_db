/*
 * FieldConfig.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "FieldConfig.h"

FieldConfig::FieldConfig():name_(""), dtype_(Data_type::UNKNOWN) {
	// TODO Auto-generated constructor stub

}

FieldConfig::FieldConfig(std::string name, std::string type) :
		name_(name) {
	if (type == "INT") {
		dtype_ = Data_type::INT;
	} else if (type == "VAR") {
		dtype_ = Data_type::VAR;
	} else if (type == "FLOAT") {
		dtype_ = Data_type::FLOAT;
	}else if (type == "TIME") {
		dtype_ = Data_type::TIME;
	}else {
		dtype_ = Data_type::UNKNOWN;
	}

}

FieldConfig::~FieldConfig() {
	// TODO Auto-generated destructor stub
}

std::string FieldConfig::getName() const {
	return this->name_;
}
void FieldConfig::setName(std::string pp) {
	this->name_ = pp;
}

Data_type FieldConfig::getType() const{
	return this->dtype_;
}

std::ostream & operator<<(std::ostream &os, const FieldConfig &fc) {
		std::string type;
		if (fc.dtype_ ==  Data_type::INT) {
			type = "int";
		} else if (fc.dtype_ ==  Data_type::VAR) {
			type = "vachar";
		} else if (fc.dtype_ == Data_type::FLOAT) {
			type = "float";
		}else if (fc.dtype_ == Data_type::TIME) {
			type= "time";
		}
		else {
			type= "unknown";
		}

        return os <<""<<fc.name_ <<"["<<type<<"] ";
}
