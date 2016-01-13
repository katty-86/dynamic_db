/*
 * FieldConfig.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "FieldConfig.h"

FieldConfig::FieldConfig(std::string name, std::string type) :
		name(name) {
	if (type == "INT") {
		dtype = DataType::INT;
	} else if (type == "VAR") {
		dtype = DataType::VAR;
	} else if (type == "FLOAT") {
		dtype = DataType::FLOAT;
	} else if (type == "TIME") {
		dtype = DataType::TIME;
	} else {
		dtype = DataType::UNKNOWN;
	}

}

FieldConfig::~FieldConfig() {
	// TODO Auto-generated destructor stub
}

std::string FieldConfig::getName() const {
	return this->name;
}
void FieldConfig::setName(const std::string pp) {
	this->name = pp;
}

DataType FieldConfig::getType() const {
	return this->dtype;
}

std::string FieldConfig::getTypeString() const {
	std::string type;
	if (this->dtype == DataType::INT) {
		type = "INT";
	} else if (this->dtype == DataType::VAR) {
		type = "VAR";
	} else if (this->dtype == DataType::FLOAT) {
		type = "FLOAT";
	} else if (this->dtype == DataType::TIME) {
		type = "TIME";
	} else {
		type = "unknown";
	}
	return type;
}

std::string FieldConfig::getNameType() const {
	std::string type = this->name;
	type.append("[");
	if (dtype == DataType::INT) {
		type.append("INT");
	} else if (dtype == DataType::VAR) {
		type.append("VAR");
	} else if (dtype == DataType::FLOAT) {
		type.append("FLOAT");
	} else if (dtype == DataType::TIME) {
		type.append("TIME");
	} else {
		type.append("unknown");
	}
	type.append("]");

	return type;
}

std::ostream & operator<<(std::ostream &os, const FieldConfig &fc) {
	std::string type;
	if (fc.dtype == DataType::INT) {
		type = "INT";
	} else if (fc.dtype == DataType::VAR) {
		type = "VAR";
	} else if (fc.dtype == DataType::FLOAT) {
		type = "FLOAT";
	} else if (fc.dtype == DataType::TIME) {
		type = "TIME";
	} else {
		type = "unknown";
	}

	return os << "" << fc.name << "[" << type << "]:";
}

