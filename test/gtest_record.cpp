# include "gtest/gtest.h"
#include <memory>
#include "Record.h"
#include "FieldConfig.h"


class RecordTest : public ::testing::Test {
protected:
	std::vector<FieldConfig> vec_config;
	std::shared_ptr<Record> record ;

	virtual void SetUp(){
		vec_config.push_back(FieldConfig("ID", "INT"));
			vec_config.push_back(FieldConfig("IMIE", "VAR"));
			vec_config.push_back(FieldConfig("FL", "FLOAT"));
			vec_config.push_back(FieldConfig("CZAS", "TIME"));
		record = std::make_shared<Record>();

	}
	virtual void TearDown(){

	}



};


TEST_F(RecordTest, addingRecordFromString){
	std::string record_s =" 1; SSSS; 13.2; 1111111;";
	std::ostringstream oss;
	EXPECT_TRUE(record->addRecord(vec_config, record_s));
	oss<<*(record);
	EXPECT_STREQ(record_s.c_str(), (oss.str()).c_str());
	//record_s.clear();
	record_s =" 11.3; SSSS; 13.2; 1111111;";
	record.reset(new Record);
	EXPECT_FALSE(record->addRecord(vec_config, record_s));
	record_s =" 11; SSS.....S; 13.2; 1111111;";
	record.reset(new Record);
	EXPECT_FALSE(record->addRecord(vec_config, record_s));
	record_s =" wwwwwwww";
	record.reset(new Record);
	EXPECT_FALSE(record->addRecord(vec_config, record_s));
	record_s =" ;;;;";
	record.reset(new Record);
	EXPECT_FALSE(record->addRecord(vec_config, record_s));
	record_s =" ;ss;12.3;11111;";
	record.reset(new Record);
	EXPECT_FALSE(record->addRecord(vec_config, record_s));
	record_s =" 1;ss;12.3;11111;";
	record.reset(new Record);
	EXPECT_TRUE(record->addRecord(vec_config, record_s));

}



TEST_F(RecordTest, addingRecordFromVector){
	std::vector<std::pair<std::string, std::string>> vps;
	vps.push_back(std::pair<std::string, std::string>("1", ""));
	vps.push_back(std::pair<std::string, std::string>("ss", ""));
	vps.push_back(std::pair<std::string, std::string>("1.2", ""));
	vps.push_back(std::pair<std::string, std::string>("111111", ""));
	EXPECT_TRUE(record->addRecord(vec_config, vps));


	vps.clear();
	vps.push_back(std::pair<std::string, std::string>("1.0", ""));
	vps.push_back(std::pair<std::string, std::string>("ss...11", ""));
	vps.push_back(std::pair<std::string, std::string>("1.2", ""));
	vps.push_back(std::pair<std::string, std::string>("111111", ""));
	record.reset(new Record);
	EXPECT_FALSE(record->addRecord(vec_config, vps));


	vps.clear();
	vps.push_back(std::pair<std::string, std::string>("1", ""));
	vps.push_back(std::pair<std::string, std::string>("SSSS", ""));
	vps.push_back(std::pair<std::string, std::string>("13.2", ""));
	vps.push_back(std::pair<std::string, std::string>("1111111", ""));
	record.reset(new Record);
	EXPECT_TRUE(record->addRecord(vec_config, vps));
	std::string record_s =" 1; SSSS; 13.2; 1111111;";
	std::ostringstream oss;
	oss<<*(record);
	EXPECT_STREQ(record_s.c_str(), (oss.str()).c_str());
}

TEST_F(RecordTest, comapreRecord){
	std::vector<std::pair<std::string, std::string>> vps;
	vps.push_back(std::pair<std::string, std::string>("1", ""));
	vps.push_back(std::pair<std::string, std::string>("imie", ""));
	vps.push_back(std::pair<std::string, std::string>("1.2", ""));
	vps.push_back(std::pair<std::string, std::string>("111111", ""));
	record->addRecord(vec_config, vps);
	EXPECT_TRUE(record->compareRecord("imie",1));
	EXPECT_FALSE(record->compareRecord("imie",2));
	EXPECT_TRUE(record->compareRecord("1",0));
	EXPECT_TRUE(record->compareRecord("1.2",2));
	EXPECT_FALSE(record->compareRecord("imie  ",1));
	EXPECT_FALSE(record->compareRecord("11111",3));

}


TEST_F(RecordTest, updateRecord){
	std::vector<std::pair<std::string, std::string>> vps;
	vps.push_back(std::pair<std::string, std::string>("1", ""));
	vps.push_back(std::pair<std::string, std::string>("SSSS", ""));
	vps.push_back(std::pair<std::string, std::string>("13.2", ""));
	vps.push_back(std::pair<std::string, std::string>("1111111", ""));
	record->addRecord(vec_config, vps);
	EXPECT_FALSE(record->updateRecord("22.0", 1,  DataType::INT));
	EXPECT_FALSE(record->updateRecord("ssss", 0,  DataType::INT));
	EXPECT_FALSE(record->updateRecord("ssss", 0,  DataType::FLOAT));

	record->updateRecord("22", 0,  DataType::INT);
	std::string record_s =" 22; SSSS; 13.2; 1111111;";
	std::ostringstream oss;
	oss<<*(record);
	EXPECT_STREQ(record_s.c_str(), (oss.str()).c_str());

	record->updateRecord("22", 1,  DataType::VAR);
	oss.clear();
	oss.str("");
	oss<<*(record);
	EXPECT_STREQ(" 22; 22; 13.2; 1111111;", (oss.str()).c_str());

	record->updateRecord("22.0", 2,  DataType::FLOAT);
	oss.clear();
	oss.str("");
	oss<<*(record);
	EXPECT_STREQ(" 22; 22; 22; 1111111;", (oss.str()).c_str());

	record->updateRecord("22", 3,  DataType::TIME);
	record_s =" 22; 22; 22; 22;";
	oss.clear();
	oss.str("");
	oss<<*(record);
	EXPECT_STREQ(record_s.c_str(), (oss.str()).c_str());
}

