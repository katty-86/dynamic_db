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
		std::cout << "Set correct value of integer for field ["<<s<< "]: ";
		std::cin >> value;
	} while (value.find_first_not_of("0123456789") != std::string::npos);

	return std::atoi(value.c_str());
}

int readString(std::string s) {
	std::string value;
	do {
		std::cout << "Set correct value of string for field ["<<s<< "]: ";
		std::cin >> value;
	} while (value.find_first_not_of("0123456789") != std::string::npos);

	return std::atoi(value.c_str());
}
