# include "gtest/gtest.h"
#include <memory>
#include <string>
#include "Table.h"
#include "FieldConfig.h"

std::map<std::string, DataType> acceptable_type { { "INT", DataType::INT }, {
		"VAR", DataType::VAR }, { "FLOAT", DataType::FLOAT }, { "TIME",
		DataType::TIME }, { "UNKNOWN", DataType::UNKNOWN }, };

class CreateTableTest: public ::testing::Test {
protected:
	std::shared_ptr<Table> t;
	std::vector<std::pair<std::string, std::string>> values;

	virtual void SetUp() {
		t = std::make_shared<Table>();
		values.push_back(std::pair<std::string, std::string>("INT", "N_INT"));
		values.push_back(std::pair<std::string, std::string>("VAR", "N_VAR"));
		values.push_back(
				std::pair<std::string, std::string>("FLOAT", "N_FLOAT"));
		values.push_back(std::pair<std::string, std::string>("TIME", "N_TIME"));
		values.shrink_to_fit();
		t->createTable("test", values);

	}
	virtual void TearDown() {

	}

};

TEST_F(CreateTableTest, CreateTable) {

	EXPECT_STREQ(t->getName().c_str(), "test");
	//EXPECT_EQ(4, (t->getVec_config()).size());
	auto fc=t->getVec_config();
	auto i=fc.back();
	EXPECT_STREQ(i.getName().c_str(), "N_TIME");
	EXPECT_STREQ(i.getTypeString().c_str(), "TIME");
	fc.pop_back();
	i=fc.back();
	EXPECT_STREQ(i.getName().c_str(), "N_FLOAT");
	EXPECT_STREQ(i.getTypeString().c_str(), "FLOAT");
	fc.pop_back();
	i=fc.back();
	EXPECT_STREQ(i.getName().c_str(), "N_VAR");
	EXPECT_STREQ(i.getTypeString().c_str(), "VAR");
	fc.pop_back();
	i=fc.back();
	EXPECT_STREQ(i.getName().c_str(), "N_INT");
	EXPECT_STREQ(i.getTypeString().c_str(), "INT");

}
