/*
 * Utils.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: kaky
 */

#include "Utils.h"

int readIntger(std::string s) {
	std::string value;
	do {
		std::cout << "Set correct value of integer for field [" << s << "]: ";
		std::cin >> value;
		std::cin.ignore(256, '\n');
	} while (value.find_first_not_of("0123456789") != std::string::npos);

	return std::atoi(value.c_str());
}

std::string readString(std::string s) {
	std::string value;
	std::cout << "Set correct value of string for field [" << s << "]: ";
	std::cin >> value;
	std::cin.ignore(256, '\n');
	std::transform(value.begin(), value.end(), value.begin(), ::toupper);
	return value;
}

float readFloat(std::string s) {
	std::string value;
	std::regex reg_float("[0-9]+\\.{1}[0-9]+(f|F)?");
	do {
		std::cout << "Set correct value of float for field [" << s << "]: ";
		std::cin >> value;
		std::cin.ignore(256, '\n');
	} while (!std::regex_match(value, reg_float));

	return std::stof(value.c_str());
}

bool checkIfInt(std::string i){
	std::regex reg_int("[[:s:]]*[0-9]+");
	return std::regex_match(i, reg_int);
}
bool checkIfVar(std::string pp){
	transform(pp.begin(), pp.end(), pp.begin(), ::toupper);
	if(pp.find_first_not_of("ABCDEFGHIJKLMNOPRSTUVWXYZQ ") == std::string::npos){
			return true;
		}
		return false;
}
bool checkIfFloat(std::string pp){
	std::regex reg_float("[0-9]+\\.{1}[0-9]+(f|F)?");
	return std::regex_match(pp, reg_float);
}
