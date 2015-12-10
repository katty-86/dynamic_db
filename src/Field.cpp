/*
 * Field.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "Field.h"

Field::Field() :
		name_("") {
	// TODO Auto-generated constructor stub

}
Field::Field(std::string n) :
		name_(n) {
	// TODO Auto-generated constructor stub

}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

std::string Field::Field::getName() const {
	return this->name_;
}
void Field::setName(std::string pp) {
	this->name_ = pp;
}
