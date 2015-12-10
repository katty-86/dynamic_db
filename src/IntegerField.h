/*
 * IntegerField.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef INTEGERFIELD_H_
#define INTEGERFIELD_H_
#include <string>
#include "Field.h"

class IntegerField: public Field {
private:
	int value_;
	friend std::ostream & operator<<(std::ostream &os, const IntegerField &inf);
public:
	IntegerField();
	IntegerField(int i, std::string name);
	~IntegerField();
	int getValue() const;
	void setValue(int pp);

};

#endif /* INTEGERFIELD_H_ */
