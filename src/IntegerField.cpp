/*
 * IntegerField.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "IntegerField.h"

IntegerField::IntegerField() :
		value_(0) {
	// TODO Auto-generated constructor stub

}
IntegerField::IntegerField(int i, std::string name) :
		value_(i), Field(name) {
	// TODO Auto-generated constructor stub

}

IntegerField::~IntegerField() {
	// TODO Auto-generated destructor stub
}

int IntegerField::getValue() const {
	return this->value_;
}
void IntegerField::setValue(int pp) {
	this->value_ = pp;
}

