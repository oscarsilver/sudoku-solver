#include <iostream>
#include <string>
#include "gtest/gtest.h"

const std::string unsolvedBoardString = "020810740700003100090002805009040087400208003160030200302700060005600008076051090";

TEST(BoardParsing, ReadBoardFromString){
	const std::string s2(unsolvedBoardString);
	EXPECT_EQ(0, s2.compare(unsolvedBoardString));
	EXPECT_EQ(1,1);
}

TEST(BoardParsing, CheckBoardLength){
	EXPECT_EQ(81, unsolvedBoardString.size());
}

TEST(Testing, SecondTest){
	EXPECT_NE(2,1);
}

GTEST_API_ int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}