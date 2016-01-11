# include "gtest/gtest.h"
#include <memory>
#include "Record.h"
#include "FieldConfig.h"


class RecordTest : public ::testing::Test {
protected:
	std::vector<FieldConfig> vec_config;
	std::shared_ptr<Record> record ;

	virtual void SetUp(){
		vec_config.push_back(FieldConfig("INT", "ID"));
		vec_config.push_back(FieldConfig("VAR", "IMIE"));
		vec_config.push_back(FieldConfig("FLOAT", "KWOTA"));
		vec_config.push_back(FieldConfig("TIME", "CZAS"));
		record = std::make_shared<Record>();

	}
	virtual void TearDown(){

	}



};


TEST_F(RecordTest, addingRecord){
	record->addRecord(vec_config, " 1; SSSS; 13.2f; 1111111");



}
