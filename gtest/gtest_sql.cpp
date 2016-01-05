//test_factorial.cpp
#include <string>
# include "gtest/gtest.h"
# include "SQL.h"
# include "Utils.h"

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
	EXPECT_EQ(false,
			sql->readSQL(std::string("select * from Customer"),
					std::string("Customer1")));
	EXPECT_EQ(true,
			sql->readSQL(std::string("select * from Customer"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(std::string("select * from Customer where test =test"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("select * from Customer where test, test"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("select * fromCustomer"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(std::string("select count(*) from Customer"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(
					std::string(
							"select count(*) from Customer where imie =test"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(std::string("select imie, test from Customer"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(
					std::string(
							"select imire,test from Customer where imie =test"),
					std::string("Customer")));
}

TEST_F(SQLTest, selectchekingFlag) {
	SQL sqla, sqlb, sqlc, sqld;
	std::pair<std::string, std::string> pairs;
	string first, second;
	sqla.readSQL(std::string("select * from Customer"),
			std::string("Customer"));
	EXPECT_EQ('S', sqla.statement);
	EXPECT_EQ(true, sqla.flag_all);
	EXPECT_EQ(false, sqla.flag_count);
	EXPECT_EQ(0, sqla.expression.size());
	EXPECT_EQ(0, sqla.where_condition.size());

	sqlb.readSQL(std::string("select count(*) from Customer where imie = test"),
			std::string("Customer"));
	EXPECT_EQ('S', sqla.statement);
	EXPECT_EQ(false, sqlb.flag_all);
	EXPECT_EQ(true, sqlb.flag_count);
	EXPECT_EQ(0, sqlb.expression.size());
	EXPECT_EQ(1, sqlb.where_condition.size());

	sqlc.readSQL(std::string("select imie from Customer where imie = 'test'"),
			std::string("Customer"));
	EXPECT_EQ('S', sqla.statement);
	EXPECT_EQ(false, sqlc.flag_all);
	EXPECT_EQ(false, sqlc.flag_count);
	EXPECT_EQ(1, sqlc.expression.size());
	EXPECT_EQ(1, sqlc.where_condition.size());
	pairs = sqlc.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("", second.c_str());
	pairs = sqlc.where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());


	sqld.readSQL(std::string("select imie,test from Customer where imie=test"),
			std::string("Customer"));
	EXPECT_EQ('S', sqla.statement);
	EXPECT_EQ(false, sqld.flag_all);
	EXPECT_EQ(false, sqld.flag_count);
	EXPECT_EQ(2, sqld.expression.size());
	EXPECT_EQ(1, sqld.where_condition.size());
	pairs = sqld.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("TEST", first.c_str());
	EXPECT_STREQ("", second.c_str());
	sqld.expression.pop_back();
	pairs = sqld.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("", second.c_str());
	pairs = sqld.where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());

}

TEST_F(SQLTest, basicInsert) {
	EXPECT_EQ(false,
			sql->readSQL(std::string("insert into customer"),
					std::string("Customer1")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("insert into Customer"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(
					std::string("insert into Customer values (wwww,www,12)"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("insert into Customer values wwww,www,12"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("insert into Customer values wwww;www;12"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("insert into Customer values ,,"),
					std::string("Customer")));
}

TEST_F(SQLTest, InsertchekingFlag) {
	SQL sqla, sqlb, sqlc;
	std::pair<std::string, std::string> pairs;
	string first, second;
	sqla.readSQL(std::string("Insert into Customer"), std::string("Customer"));
	EXPECT_EQ('0', sqla.statement);
	EXPECT_EQ(false, sqla.flag_all);
	EXPECT_EQ(false, sqla.flag_count);
	EXPECT_EQ(0, sqla.expression.size());
	EXPECT_EQ(0, sqla.where_condition.size());

	sqlb.readSQL(
			std::string("insert into Customer values (imie, nazwisko, wiek)"),
			std::string("Customer"));
	EXPECT_EQ('I', sqlb.statement);
	EXPECT_EQ(3, sqlb.expression.size());
	EXPECT_EQ(0, sqlb.where_condition.size());
	pairs = sqlb.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("WIEK", first.c_str());
	EXPECT_STREQ("", second.c_str());
	sqlb.expression.pop_back();
	pairs = sqlb.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("NAZWISKO", first.c_str());
	EXPECT_STREQ("", second.c_str());
	sqlb.expression.pop_back();
	pairs = sqlb.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("", second.c_str());


	sqlc.readSQL(std::string("insert into from Customer where imie = test"),
			std::string("Customer"));
	EXPECT_EQ('0', sqlc.statement);
	EXPECT_EQ(0, sqlc.expression.size());
	EXPECT_EQ(0, sqlc.where_condition.size());

}

TEST_F(SQLTest, basicUpdate) {
	EXPECT_EQ(false,
			sql->readSQL(std::string("Update Customer set "),
					std::string("Customer1")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("Update Customer set "),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(
					std::string(
							"Update Customer set test= test where cos =cps"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("Update Customer set "),
					std::string("Customer1")));
	EXPECT_EQ(true,
			sql->readSQL(
					std::string(
							"Update Customer set test= test where cos =cps"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(
					std::string(
							"Update Customer set test = test where cos =cps"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(
					std::string(
							"Update Customer set test,test1 where cos =cps"),
					std::string("Customer")));
}

TEST_F(SQLTest, UpdatechekingFlag) {
	SQL sqla, sqlb, sqlc, sqld, sqle, sqlf;
	std::pair<std::string, std::string> pairs;
	string first, second;
	sqla.readSQL(std::string("Update Customer set "), std::string("Customer"));
	EXPECT_EQ('0', sqla.statement);
	EXPECT_EQ(false, sqla.flag_all);
	EXPECT_EQ(false, sqla.flag_count);
	EXPECT_EQ(0, sqla.expression.size());
	EXPECT_EQ(0, sqla.where_condition.size());

	sqlb.readSQL(std::string("Update Customer set test=test1 where imie=ania"),
			std::string("Customer"));
	EXPECT_EQ('U', sqlb.statement);
	EXPECT_EQ(1, sqlb.expression.size());
	EXPECT_EQ(1, sqlb.where_condition.size());
	pairs = sqlb.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("TEST", first.c_str());
	EXPECT_STREQ("TEST1", second.c_str());

	pairs = sqlb.where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("ANIA", second.c_str());


	sqle.readSQL(
			std::string("Update Customer set test = est1 where imie= kon"),
			std::string("Customer"));
	EXPECT_EQ('U', sqle.statement);
	EXPECT_EQ(1, sqle.expression.size());
	EXPECT_EQ(1, sqle.where_condition.size());

	pairs = sqle.expression.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("TEST", first.c_str());
	EXPECT_STREQ("EST1", second.c_str());
	pairs = sqle.where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("KON", second.c_str());

	sqlc.readSQL(std::string("Update Customer set test where cos = cps"),
			std::string("Customer"));
	EXPECT_EQ('0', sqlc.statement);
	EXPECT_EQ(0, sqlc.expression.size());
	EXPECT_EQ(0, sqlc.where_condition.size());

	sqld.readSQL(std::string("Update Customer set test= where cos = cps"),
			std::string("Customer"));
	EXPECT_EQ('0', sqld.statement);
	EXPECT_EQ(0, sqld.expression.size());
	EXPECT_EQ(0, sqld.where_condition.size());

	sqlf.readSQL(std::string("Update Customer set where cos = cps"),
			std::string("Customer"));
	EXPECT_EQ('0', sqlf.statement);
	EXPECT_EQ(0, sqlf.expression.size());
	EXPECT_EQ(0, sqlf.where_condition.size());
}

TEST_F(SQLTest, basicDelete) {
	EXPECT_EQ(false,
			sql->readSQL(std::string("Delete from Customer "),
					std::string("Customer1")));
	EXPECT_EQ(true,
			sql->readSQL(std::string("Delete from customer"),
					std::string("Customer")));
	EXPECT_EQ(true,
			sql->readSQL(std::string("delete from customer where cos =cps"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(std::string("delete from customer where cos ,cps"),
					std::string("Customer")));
	EXPECT_EQ(false,
			sql->readSQL(
					std::string(
							"delete from customer set test = test where cos =cps"),
					std::string("Customer")));
}

TEST_F(SQLTest, deletetchekingFlag) {
	SQL sqla, sqlb, sqlc, sqld;
	std::pair<std::string, std::string> pairs;
	string first, second;
	sqla.readSQL(std::string("delete from Customer"),
			std::string("Customer"));
	EXPECT_EQ('D', sqla.statement);
	EXPECT_EQ(false, sqla.flag_all);
	EXPECT_EQ(false, sqla.flag_count);
	EXPECT_EQ(0, sqla.expression.size());
	EXPECT_EQ(0, sqla.where_condition.size());

	sqlb.readSQL(std::string("delete (*) from Customer where imie = test"),
			std::string("Customer"));
	EXPECT_EQ('0', sqlb.statement);
	EXPECT_EQ(false, sqlb.flag_all);
	EXPECT_EQ(false, sqlb.flag_count);
	EXPECT_EQ(0, sqlb.expression.size());
	EXPECT_EQ(0, sqlb.where_condition.size());

	int flag = sqlc.readSQL(std::string("delete from Customer where imie = 'test'"),
			std::string("Customer"));
	EXPECT_EQ(true, flag);
	EXPECT_EQ('D', sqlc.statement);
	EXPECT_EQ(false, sqlc.flag_all);
	EXPECT_EQ(false, sqlc.flag_count);
	EXPECT_EQ(0, sqlc.expression.size());
	EXPECT_EQ(1, sqlc.where_condition.size());
	pairs = sqlc.where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());


	sqld.readSQL(std::string("delete from Customer where imie=test"),
			std::string("Customer"));
	EXPECT_EQ('D', sqld.statement);
	EXPECT_EQ(false, sqld.flag_all);
	EXPECT_EQ(false, sqld.flag_count);
	EXPECT_EQ(0, sqld.expression.size());
	EXPECT_EQ(1, sqld.where_condition.size());
	pairs = sqld.where_condition.back();
	first = pairs.first;
	second = pairs.second;
	EXPECT_STREQ("IMIE", first.c_str());
	EXPECT_STREQ("TEST", second.c_str());
}
