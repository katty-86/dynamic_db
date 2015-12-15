/*
 * Table.h
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */

#ifndef SRC_TABLE_H_
#define SRC_TABLE_H_
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "Record.h"
#include "FieldConfig.h"
#include <memory>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class Table {
	std::string name_;
	std::vector<FieldConfig> vec_config_;
	std::list<Record> list_data_;
	friend class boost::serialization::access;
	template<class Archive>
	 void serialize(Archive &ar, const unsigned int version)
	    {
	        ar & name_;
	        ar & vec_config_;
	        ar & list_data_;
	    }

public:
	Table();
	~Table();
	std::string getName() const;
	void setName(std::string pp);
	void addConfigField(std::string type, std::string name);
	void addRow();
	void describeTable();
	void printTable();
	void read_data(Table &s, std::string filename);
	void save_data(const Table &s, std::string filename);

	//not implemented
	//int delete_row();

};

#endif /* SRC_TABLE_H_ */
