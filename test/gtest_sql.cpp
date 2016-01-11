//test_factorial.cpp
#include <string>
# include "gtest/gtest.h"
# include "SQL.h"

using namespace std;

class SQLTest: public ::testing::Test {
protected:
	SQL *sql;

	virtual void SetUp() {
	}
	virtual void TearDown() {
	}
	SQLTest() {
		sql = new SQL();
	}
	~SQLTest() {
		delete sql;
	}
};

TEST_F(SQLTest, basicSelect) {

	bool testval= sql->readSQL(std::string("select * from Customer"), std::string("Customer1"));
	EXPECT_FALSE(testval);

	EXPECT_TRUE(
			sql->readSQL(std::string("select * from Customer"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(std::string("select * from Customer where test =test"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(std::string("select * from Customer where test, test"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(std::string("select * fromCustomer"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(std::string("select count(*) from Customer"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(
					std::string(
							"select count(*) from Customer where imie =test"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(std::string("select imie, test from Customer"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(
					std::string(
							"select imire,test from Customer where imie =test"),
					std::string("Customer")));
}

TEST_F(SQLTest, selectchekingFlag) {
	std::pair<std::string, std::string> pairs;
	string first, second;
	sql->readSQL(std::string("select * from Customer"),
			std::string("Customer"));
	EXPECT_EQ('S', sql->statement);
	EXPECT_TRUE( sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

	sql->readSQL(std::string("select count(*) from Customer where imie = test"),
			std::string("Customer"));
	EXPECT_EQ('S', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_TRUE( sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(1, sql->where_condition.size());

	sql->readSQL(std::string("select imie from Customer where imie = 'test'"),
			std::string("Customer"));
	EXPECT_EQ('S', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(1, sql->expression.size());
	EXPECT_EQ(1, sql->where_condition.size());
	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("", second.c_str());
	pairs = sql->where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());


	sql->readSQL(std::string("select imie,test from Customer where imie=test"),
			std::string("Customer"));
	EXPECT_EQ('S', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(2, sql->expression.size());
	EXPECT_EQ(1, sql->where_condition.size());
	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("TEST", first.c_str());
	EXPECT_STREQ("", second.c_str());
	sql->expression.pop_back();
	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("", second.c_str());
	pairs = sql->where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());

}

TEST_F(SQLTest, basicInsert) {
	EXPECT_FALSE(
			sql->readSQL(std::string("insert into customer"),
					std::string("Customer1")));
	EXPECT_FALSE(
			sql->readSQL(std::string("insert into Customer"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(
					std::string("insert into Customer values (wwww,www,12)"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(std::string("insert into Customer values wwww,www,12"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(std::string("insert into Customer values wwww;www;12"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(std::string("insert into Customer values ,,"),
					std::string("Customer")));
}

TEST_F(SQLTest, InsertchekingFlag) {
	std::pair<std::string, std::string> pairs;
	string first, second;
	sql->readSQL(std::string("Insert into Customer"), std::string("Customer"));
	EXPECT_EQ('0', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_FALSE(sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

	sql->readSQL(
			std::string("insert into Customer values (imie, nazwisko, wiek)"),
			std::string("Customer"));
	EXPECT_EQ('I', sql->statement);
	EXPECT_EQ(3, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());
	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("WIEK", first.c_str());
	EXPECT_STREQ("", second.c_str());
	sql->expression.pop_back();
	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("NAZWISKO", first.c_str());
	EXPECT_STREQ("", second.c_str());
	sql->expression.pop_back();
	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("", second.c_str());


	sql->readSQL(std::string("insert into from Customer where imie = test"),
			std::string("Customer"));
	EXPECT_EQ('0', sql->statement);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

}

TEST_F(SQLTest, basicUpdate) {
	EXPECT_FALSE(
			sql->readSQL(std::string("Update Customer set "),
					std::string("Customer1")));
	EXPECT_FALSE(
			sql->readSQL(std::string("Update Customer set "),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(
					std::string(
							"Update Customer set test= test where cos =cps"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(std::string("Update Customer set "),
					std::string("Customer1")));
	EXPECT_TRUE(
			sql->readSQL(
					std::string(
							"Update Customer set test= test where cos =cps"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(
					std::string(
							"Update Customer set test = test where cos =cps"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(
					std::string(
							"Update Customer set test,test1 where cos =cps"),
					std::string("Customer")));
}

TEST_F(SQLTest, UpdatechekingFlag) {
	std::pair<std::string, std::string> pairs;
	string first, second;
	sql->readSQL(std::string("Update Customer set "), std::string("Customer"));
	EXPECT_EQ('0', sql->statement);
	EXPECT_FALSE(sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

	sql->readSQL(std::string("Update Customer set test=test1 where imie=ania"),
			std::string("Customer"));
	EXPECT_EQ('U', sql->statement);
	EXPECT_EQ(1, sql->expression.size());
	EXPECT_EQ(1, sql->where_condition.size());
	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("TEST", first.c_str());
	EXPECT_STREQ("TEST1", second.c_str());

	pairs = sql->where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("ANIA", second.c_str());


	sql->readSQL(
			std::string("Update Customer set test = est1 where imie= kon"),
			std::string("Customer"));
	EXPECT_EQ('U', sql->statement);
	EXPECT_EQ(1, sql->expression.size());
	EXPECT_EQ(1, sql->where_condition.size());

	pairs = sql->expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("TEST", first.c_str());
	EXPECT_STREQ("EST1", second.c_str());
	pairs = sql->where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("KON", second.c_str());

	sql->readSQL(std::string("Update Customer set test where cos = cps"),
			std::string("Customer"));
	EXPECT_EQ('0', sql->statement);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

	sql->readSQL(std::string("Update Customer set test= where cos = cps"),
			std::string("Customer"));
	EXPECT_EQ('0', sql->statement);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

	sql->readSQL(std::string("Update Customer set where cos = cps"),
			std::string("Customer"));
	EXPECT_EQ('0', sql->statement);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());
}

TEST_F(SQLTest, basicDelete) {
	EXPECT_FALSE(
			sql->readSQL(std::string("Delete from Customer "),
					std::string("Customer1")));
	EXPECT_TRUE(
			sql->readSQL(std::string("Delete from customer"),
					std::string("Customer")));
	EXPECT_TRUE(
			sql->readSQL(std::string("delete from customer where cos =cps"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(std::string("delete from customer where cos ,cps"),
					std::string("Customer")));
	EXPECT_FALSE(
			sql->readSQL(
					std::string(
							"delete from customer set test = test where cos =cps"),
					std::string("Customer")));
}

TEST_F(SQLTest, deletetchekingFlag) {
	std::pair<std::string, std::string> pairs;
	string first, second;
	sql->readSQL(std::string("delete from Customer"),
			std::string("Customer"));
	EXPECT_EQ('D', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

	sql->readSQL(std::string("delete (*) from Customer where imie = test"),
			std::string("Customer"));
	EXPECT_EQ('0', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(0, sql->where_condition.size());

	int flag = sql->readSQL(std::string("delete from Customer where imie = 'test'"),
			std::string("Customer"));
	EXPECT_TRUE( flag);
	EXPECT_EQ('D', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(1, sql->where_condition.size());
	pairs = sql->where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());


	sql->readSQL(std::string("delete from Customer where imie=test"),
			std::string("Customer"));
	EXPECT_EQ('D', sql->statement);
	EXPECT_FALSE( sql->flag_all);
	EXPECT_FALSE( sql->flag_count);
	EXPECT_EQ(0, sql->expression.size());
	EXPECT_EQ(1, sql->where_condition.size());
	pairs = sql->where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());
}

