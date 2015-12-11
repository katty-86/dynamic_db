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
#include <memory>

enum class Data_type {
	VAR=1, INT=2, FLOAT=3, TIME=4,UNKNOWN=6
};

class FieldConfig {
	std::string name_;
	Data_type dtype_;
	friend std::ostream & operator<<(std::ostream &os, const FieldConfig &fc);
public:
	FieldConfig();
	FieldConfig(std::string name, std::string type);
	~FieldConfig();
	std::string getName() const;
	void setName(std::string pp);
};

#endif /* SRC_FIELDCONFIG_H_ */
