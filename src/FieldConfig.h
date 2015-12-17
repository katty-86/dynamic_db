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
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

enum class Data_type {
	VAR = 1, INT = 2, FLOAT = 3, TIME = 4, UNKNOWN = 6
};

class FieldConfig {
	std::string name_;
	Data_type dtype_;
	friend std::ostream & operator<<(std::ostream &os, const FieldConfig &fc);
	/*friend class boost::serialization::access;
	 template<class Archive>
	 void serialize(Archive & ar, const unsigned int version) {
	 ar & name_;
	 ar & dtype_;
	 }*/
public:
	FieldConfig();
	FieldConfig(std::string name, std::string type);
	~FieldConfig();
	std::string getName() const;
	void setName(std::string pp);
	Data_type getType() const;
	std::string getTypeString();
	std::string getNameType();
};

#endif /* SRC_FIELDCONFIG_H_ */
