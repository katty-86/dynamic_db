/*
 * Field.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#include <string>
#include <iostream>
#include <sstream>

class Any_Field {
public:
	virtual ~Any_Field() {
	}
	virtual void print() = 0;
	virtual std::string getValueString() = 0;
};

template<class T>
class Field: public Any_Field {
public:
	Field(const T& value) :
			value_(value) {
	}

	virtual void print() {
		std::cout << value_ << '\n';
	}

	void setValue(const T& value) {
		this->value_ = value;
	}

	T getValue() {
		return this->value_;
	}

	std::string getValueString()  {
		std::ostringstream oss;
		oss << this->value_;
		return oss.str();
	}
private:
	T value_;
	friend std::ostream & operator<<(std::ostream &os, const Field &f) {
		std::ostringstream oss;
		oss << f.value_;
		return os << oss.str();
	}
};

