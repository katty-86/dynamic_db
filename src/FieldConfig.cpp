/*
 * FieldConfig.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "FieldConfig.h"

FieldConfig::FieldConfig() {
	// TODO Auto-generated constructor stub

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
