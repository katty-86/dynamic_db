/*
 * Record.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: kaky
 */
#include <memory>
#include "Record.h"
#include <iostream>




//void Record::addField(Field f){
//	this->record_.push_back(f);
//}
//
//bool Record::addField(std::string name, std::string type){
//	Field f;
//	bool result=true;
//	if(type=="int"){
//		f=IntegerField(1,type);
//	}else if(type=="varchar"){
//		f=VarcharField(name, type);
//	}else{
//		std::cout<<"zle"<<std::endl;
//		result=false;
//	}
//	this->record_.push_back(f);
//	return result;
//}
//
//std::ostream & operator<<(std::ostream &os, const Record & r) {
//
//        std::list<IntegerField>::const_iterator it;
//        for (it = r.record_.begin(); it != r.record_.end(); it++) {
//                os <<"\n" << *it;
//        }
//        return os;
//}
