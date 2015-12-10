/*
 * Field.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef FIELD_H_
#define FIELD_H_
#include <string>

class Field {
protected:
	std::string name_;
	std::string type_;
	friend std::ostream & operator<<(std::ostream &os, const Field &inf);
public:
	Field();
	Field(std::string n);
	~Field();
	std::string getName() const;
	void setName(std::string pp);
};

#endif /* FIELD_H_ */
