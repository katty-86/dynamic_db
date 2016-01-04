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
  virtual void TearDown() { }
  SQLTest(){
	  sql= new SQL();
  }
  ~SQLTest(){
	  delete sql;
  }
};

struct sql_state : SQL{
	string sqlString;
	bool flag_count:1;//=false;
	bool flag_all:1;//=false;
	std::vector<std::pair<std::string, std::string>> expression;
	std::vector<std::pair<std::string, std::string>> where_condition;
	bool success;
};


TEST_F(SQLTest, basicSelect) {
	EXPECT_EQ (false, sql->readSQL( std::string("select * from Customer"),std::string("Customer1")));
	EXPECT_EQ (true, sql->readSQL( std::string("select * from Customer"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("select * from Customer where test =test"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("select * from Customer where test, test"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("select * fromCustomer"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("select count(*) from Customer"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("select count(*) from Customer where imie =test"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("select imie, test from Customer"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("select imire,test from Customer where imie =test"),std::string("Customer")));
}

TEST_F(SQLTest, basicInsert) {
	EXPECT_EQ (false, sql->readSQL( std::string("insert into customer"),std::string("Customer1")));
	EXPECT_EQ (false, sql->readSQL( std::string("insert into Customer"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("insert into Customer values (wwww,www,12)"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("insert into Customer values wwww,www,12"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("insert into Customer values wwww;www;12"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("insert into Customer values ,,"),std::string("Customer")));
}

TEST_F(SQLTest, basicUpdate) {
	EXPECT_EQ (false, sql->readSQL( std::string("Update Customer set "),std::string("Customer1")));
	EXPECT_EQ (false, sql->readSQL( std::string("Update Customer set "),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("Update Customer set test= test where cos =cps"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("Update Customer set "),std::string("Customer1")));
	EXPECT_EQ (true, sql->readSQL( std::string("Update Customer set test= test where cos =cps"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("Update Customer set test = test where cos =cps"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("Update Customer set test,test1 where cos =cps"),std::string("Customer")));
}


TEST_F(SQLTest, basicDelete) {
	EXPECT_EQ (false, sql->readSQL( std::string("Delete from Customer "),std::string("Customer1")));
	EXPECT_EQ (true, sql->readSQL( std::string("Delete from customer"),std::string("Customer")));
	EXPECT_EQ (true, sql->readSQL( std::string("delete from customer where cos =cps"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("delete from customer where cos ,cps"),std::string("Customer")));
	EXPECT_EQ (false, sql->readSQL( std::string("delete from customer set test = test where cos =cps"),std::string("Customer")));
}
