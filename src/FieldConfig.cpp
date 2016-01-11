/*
 * FieldConfig.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "FieldConfig.h"

FieldConfig::FieldConfig() :
		name(""), dtype(Data_type::UNKNOWN) {
	// TODO Auto-generated constructor stub

}

FieldConfig::FieldConfig(std::string name, std::string type) :
		name(name) {
	if (type == "INT") {
		dtype = Data_type::INT;
	} else if (type == "VAR") {
		dtype = Data_type::VAR;
	} else if (type == "FLOAT") {
		dtype = Data_type::FLOAT;
	} else if (type == "TIME") {
		dtype = Data_type::TIME;
	} else {
		dtype = Data_type::UNKNOWN;
	}

}

FieldConfig::~FieldConfig() {
	// TODO Auto-generated destructor stub
}

std::string FieldConfig::getName() const {
	return this->name;
}
void FieldConfig::setName(std::string pp) {
	this->name = pp;
}

Data_type FieldConfig::getType() const {
	return this->dtype;
}

std::string FieldConfig::getTypeString() const {
	std::string type;
	if (this->dtype == Data_type::INT) {
		type = "INT";
	} else if (this->dtype == Data_type::VAR) {
		type = "VAR";
	} else if (this->dtype == Data_type::FLOAT) {
		type = "FLOAT";
	} else if (this->dtype == Data_type::TIME) {
		type = "TIME";
	} else {
		type = "unknown";
	}
	return type;
}

std::string FieldConfig::getNameType() const {
	std::string type = this->name;
	type.append("[");
	if (dtype == Data_type::INT) {
		type.append("INT");
	} else if (dtype == Data_type::VAR) {
		type.append("VAR");
	} else if (dtype == Data_type::FLOAT) {
		type.append("FLOAT");
	} else if (dtype == Data_type::TIME) {
		type.append("TIME");
	} else {
		type.append("unknown");
	}
	type.append("]");

	return type;
}

std::ostream & operator<<(std::ostream &os, const FieldConfig &fc) {
	std::string type;
	if (fc.dtype == Data_type::INT) {
		type = "INT";
	} else if (fc.dtype == Data_type::VAR) {
		type = "VAR";
	} else if (fc.dtype == Data_type::FLOAT) {
		type = "FLOAT";
	} else if (fc.dtype == Data_type::TIME) {
		type = "TIME";
	} else {
		type = "unknown";
	}

	return os << "" << fc.name << "[" << type << "]:";
}


