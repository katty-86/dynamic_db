/*
 * Utils.h
 *
 *  Created on: Dec 17, 2015
 *      Author: kaky
 */
#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_
#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include "FieldConfig.h"

enum class file_status {
	NOT_EXIST, EXIST_AND_EMPTY, EXIST_NOT_EMPTY
};

static std::map<std::string, DataType> acceptable_type {
		{ "INT", DataType::INT }, { "VAR", DataType::VAR }, { "FLOAT",
				DataType::FLOAT }, { "TIME", DataType::TIME }, { "UNKNOWN",
				DataType::UNKNOWN }, };

int readIntger(std::string s);
std::string readString(std::string s);
float readFloat(std::string s);
bool checkIfInt(std::string i);
bool checkIfVar(std::string v);
bool checkIfFloat(std::string f);
bool verifyStringIsCorrectType(std::string type, std::string value);
file_status getStatusOfFile(const std::string &filename);

#endif /* SRC_UTILS_H_ */
