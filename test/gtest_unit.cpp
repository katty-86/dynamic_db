# include "gtest/gtest.h"
# include "Utils.h"

using namespace std;

TEST(utiltest, mycheckIfIntTest) {
	EXPECT_TRUE(checkIfInt("12"));
	EXPECT_FALSE(checkIfInt("1////2"));
	EXPECT_FALSE(checkIfInt("test"));
	EXPECT_FALSE(checkIfInt("1.2"));
	EXPECT_FALSE(checkIfInt("1,2"));
}

TEST(utiltest, mycheckIfVarTest) {
	EXPECT_TRUE(checkIfVar("test"));
	EXPECT_TRUE(checkIfVar("wwwww wwwwww"));
	EXPECT_FALSE(checkIfVar("test?????"));
	EXPECT_FALSE(checkIfVar("1.2"));
	EXPECT_FALSE(checkIfVar("1,,2"));
}

TEST(utiltest, mycheckIfFloatTest) {
	EXPECT_TRUE(checkIfFloat("6.9"));
	EXPECT_TRUE(checkIfFloat("6.9f"));
	EXPECT_TRUE(checkIfFloat("6.9F"));
	EXPECT_FALSE(checkIfFloat("6888"));
	EXPECT_FALSE(checkIfFloat("wwwww wwwwww"));
	EXPECT_FALSE(checkIfFloat("test?????"));
	EXPECT_TRUE(checkIfFloat("1.2"));
}
