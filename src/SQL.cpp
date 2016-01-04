/*
 * SQL.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: kaky
 */

#include "SQL.h"

void SQL::printAll() {
		std::cout << this->statement << "flag_count " << this->flag_count
				<< "flag_all " << this->flag_all << "\n";
		for (auto a = this->expression.begin(); a != this->expression.end();
				++a) {
			std::cout << (*a).first << " " << (*a).second;
		}
		std::cout << "\n";
		for (auto a = this->where_condition.begin();
				a != this->where_condition.end(); ++a) {
			std::cout << (*a).first << " " << (*a).second;
		}
		std::cout<<std::endl;
	}


std::vector<std::pair<std::string, std::string>> SQL::buildPairVector(
		std::string str) {
	std::vector<std::pair<std::string, std::string>> vps;
	std::regex e("([[:w:]]+)[[:s:]]*=[[:s:]]*\\\'*([[:w:]]+)\\\'*");
	std::sregex_iterator pos_u(str.cbegin(), str.cend(), e);
	std::sregex_iterator end_u;
	for (; pos_u != end_u; pos_u++) {
		vps.push_back(std::pair<std::string, std::string>(pos_u->str(1), pos_u->str(2)));
	}
	return vps;
}

std::vector<std::pair<std::string, std::string>> SQL::buildStringVector(
		std::string str) {
	std::vector<std::pair<std::string, std::string>> vps;
	std::regex e("([[:w:]]+)[[:s:]]*");
	std::sregex_iterator pos_u(str.cbegin(), str.cend(), e);
	std::sregex_iterator end_u;
	for (; pos_u != end_u; pos_u++) {
		vps.push_back(std::pair<std::string, std::string>(pos_u->str(1), ""));
	}
	return vps;
}


bool SQL::readSQL(std::string str, std::string name_of_table) {
	this->flag_all=false;
	this->flag_count=false;
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	std::smatch m;

	int pos = str.find("WHERE");
	if (pos != -1) {
		std::string s_where_expression = str.substr(pos, str.size() - pos);
		this->where_condition = buildPairVector(s_where_expression);
		if (this->where_condition.empty() == true) {
			std::cout << "not correct statement" << std::endl;
			return false;
		}
	}

	if (regex_match(str,
			std::regex(
					"delete[[:s:]]+from[[:s:]]+" + name_of_table
							+ "[[:s:]]*(where[[:s:]]+[[:print:]]*)?",
							std::regex_constants::icase)) == true) {
		this->statement = 'D';
	} else if (regex_search(str, m,
			std::regex(
					"insert[[:s:]]+into[[:s:]]+" + name_of_table
							+ "[[:s:]]+values[[:s:]]+\\\({1}[[:s:]]*([[:print:]]+)\\\){1}",
							std::regex_constants::icase)) == true) {
		this->statement = 'I';
		this->expression = buildStringVector(m[1]);

	} else if (regex_match(str,
			std::regex(
					"update[[:s:]]*" + name_of_table
							+ "[[:s:]]+set[[:s:]]+(([[:w:]]+)[[:s:]]*=[[:s:]]*([[:w:]]+)*)[[:s:]]*(where[[:s:]]+[[:print:]]*)?",
							std::regex_constants::icase)) == true) {
		std::cout << "update u" << str <<std:: endl;
		regex_search(str, m,
				std::regex(
						"update[[:s:]]*" + name_of_table
								+ "[[:s:]]+set([[:print:]]*)[[:s:]]+",
								std::regex_constants::icase));
		this->statement = 'U';
		this->expression = buildPairVector(m[1]);
	} else if (regex_match(str, m,
			std::regex(
					"select[[:s:]]+([[:print:]]+)[[:s:]]+from[[:s:]]+"
							+ name_of_table
							+ "[[:s:]]*(where[[:s:]]+[[:print:]]*)?",
							std::regex_constants::icase)) == true) {
		this->statement = 'S';
		if (m[1] == "*") {
			this->flag_all = true;
		} else if (m[1] == "COUNT(*)") {
			this->flag_count = true;
		} else {
			this->expression = buildStringVector(m[1]);
		}
	} else {
		return false;
	}
	return true;

}
