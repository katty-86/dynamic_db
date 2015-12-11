/*
 * Field.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef FIELD_H_
#define FIELD_H_
#include <string>

template <class T>
class Field {
protected:
	T value;
public:
	Field();
	Field(T v);
	~Field();
	std::string getValue() const;
	void setValue(T v);
};

#endif /* FIELD_H_ */
