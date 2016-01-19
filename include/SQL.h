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
	char statement;
	bool flag_count :1; //=false;
	bool flag_all :1; //=false;
	std::string tablename;
	std::vector<std::pair<std::string, std::string>> expression;
	std::vector<std::pair<std::string, std::string>> where_condition;

	SQL(char s = '0', bool flag_c = 0, bool flag_al = 0, std::string tablename =
			"");
	~SQL();
	void printAll();
	bool readSQL(std::string str);
	std::vector<std::pair<std::string, std::string>> buildPairVector(
			std::string str);
	std::vector<std::pair<std::string, std::string>> buildStringVector(
			std::string str);
};

#endif /* SQL_H_ */
