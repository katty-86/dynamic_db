/*
 * Serializer.h
 *
 *  Created on: Dec 17, 2015
 *      Author: kaky
 */
#include "Table.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#ifndef SRC_SERIALIZER_H_
#define SRC_SERIALIZER_H_


class Serializer {
public:
	Serializer();
	~Serializer();
	bool writaData(std::shared_ptr<Table> &t, const std::string filename);
	bool readData(std::shared_ptr<Table> &t,const std::string filename);
};

#endif /* SRC_SERIALIZER_H_ */
