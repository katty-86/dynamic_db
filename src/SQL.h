/*
 * SQL.h
 *
 *  Created on: Dec 23, 2015
 *      Author: kaky
 */
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#ifndef SQL_H_
#define SQL_H_

struct SQL {
	std::string statement;
	bool flag_count=false;
	bool flag_all=false;
	std::vector<std::pair<std::string, std::string>> expression;
	std::vector<std::pair<std::string, std::string>> where_condition;

	void printAll();
	void readSQL( std::string str, std::string name_of_table);
	std::vector<std::pair<std::string, std::string>>  buidVector(std::string,std::string); //utils
	std::vector<std::pair<std::string, std::string>> buildPairVector(
			std::string str);
	std::vector<std::pair<std::string, std::string>> buildStringVector(
			std::string str);
};

#endif /* SQL_H_ */
