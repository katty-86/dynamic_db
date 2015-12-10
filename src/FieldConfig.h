/*
 * FieldConfig.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef SRC_FIELDCONFIG_H_
#define SRC_FIELDCONFIG_H_
#include <string>
#include <iostream>

enum class Data_type {
	VAR, INT, FLOAT, TIME
};

class FieldConfig {
	std::string name_;
	Data_type dtype_;
public:
	FieldConfig();
	~FieldConfig();
	std::string getName() const;
	void setName(std::string pp);
};

#endif /* SRC_FIELDCONFIG_H_ */
