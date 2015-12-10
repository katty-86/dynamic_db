/*
 * Table.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include "Table.h"



Table::Table() {
	// TODO Auto-generated constructor stub

}

Table::~Table() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
std::string Table::getName() const {
	return this->name_;
}
void Table::setName(std::string pp) {
	this->name_ = pp;
}

int Table::getFieldCounter() const{
	return this->fieldCounter_;
}
void Table::setFieldCounter(int pp){
	this->fieldCounter_=pp
}
