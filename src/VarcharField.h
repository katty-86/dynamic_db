/*
 * VarcharField.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef VARCHARFIELD_H_
#define VARCHARFIELD_H_

#include <string>
#include "Field.h"

class VarcharField: public Field {
private:
	std::string value_;
	friend std::ostream & operator<<(std::ostream &os, const VarcharField &inf);
public:
	VarcharField();
	VarcharField(std::string nam, std::string val);
	~VarcharField();
	std::string getValue() const;
	void setValue(std::string pp);
};

#endif /* VARCHARFIELD_H_ */
