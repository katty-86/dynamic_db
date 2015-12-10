/*
 * VarcharField.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "VarcharField.h"

VarcharField::VarcharField() :
		value_("") {
	// TODO Auto-generated constructor stub

}

VarcharField::VarcharField(std::string nam, std::string val) :
		value_(val), Field(nam) {
}

VarcharField::~VarcharField() {
	// TODO Auto-generated destructor stub
}

std::string VarcharField::getValue() const {
	return this->value_;
}
void VarcharField::setValue(std::string pp) {
	this->value_ = pp;
}

std::ostream & operator<<(std::ostream &os, const VarcharField &inf) {
	return os << inf.value_ << " ";
}

