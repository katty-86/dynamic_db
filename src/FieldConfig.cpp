/*
 * FieldConfig.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "FieldConfig.h"

FieldConfig::FieldConfig() :
		name_(""), dtype_(Data_type::UNKNOWN) {
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
	} else if (type == "TIME") {
		dtype_ = Data_type::TIME;
	} else {
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

Data_type FieldConfig::getType() const {
	return this->dtype_;
}

std::string FieldConfig::getTypeString() const {
	std::string type;
	if (this->dtype_ == Data_type::INT) {
		type = "INT";
	} else if (this->dtype_ == Data_type::VAR) {
		type = "VAR";
	} else if (this->dtype_ == Data_type::FLOAT) {
		type = "FLOAT";
	} else if (this->dtype_ == Data_type::TIME) {
		type = "TIME";
	} else {
		type = "unknown";
	}
	return type;
}

std::string FieldConfig::getNameType() const {
	std::string type = this->name_;
	type.append("[");
	if (dtype_ == Data_type::INT) {
		type.append("INT");
	} else if (dtype_ == Data_type::VAR) {
		type.append("VAR");
	} else if (dtype_ == Data_type::FLOAT) {
		type.append("FLOAT");
	} else if (dtype_ == Data_type::TIME) {
		type.append("TIME");
	} else {
		type.append("unknown");
	}
	type.append("]");

	return type;
}

std::ostream & operator<<(std::ostream &os, const FieldConfig &fc) {
	std::string type;
	if (fc.dtype_ == Data_type::INT) {
		type = "INT";
	} else if (fc.dtype_ == Data_type::VAR) {
		type = "VAR";
	} else if (fc.dtype_ == Data_type::FLOAT) {
		type = "FLOAT";
	} else if (fc.dtype_ == Data_type::TIME) {
		type = "TIME";
	} else {
		type = "unknown";
	}

	return os << "" << fc.name_ << "[" << type << "]:";
}

