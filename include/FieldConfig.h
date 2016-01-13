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
#include <map>

enum class DataType {
	VAR = 1, INT = 2, FLOAT = 3, TIME = 4, UNKNOWN = 6
};

class FieldConfig {
	std::string name;
	DataType dtype;
	friend std::ostream & operator<<(std::ostream &os, const FieldConfig &fc);

public:
	FieldConfig(std::string name, std::string type);
	~FieldConfig();
	std::string getName() const;
	void setName(const std::string pp);
	DataType getType() const;
	std::string getTypeString() const;
	std::string getNameType() const;

};

#endif /* SRC_FIELDCONFIG_H_ */
