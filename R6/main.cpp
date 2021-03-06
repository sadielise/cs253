#include "fib.h"
#include <gtest/gtest.h>

namespace {

// YOUR TESTS GO HERE
TEST(FibTest0, Handles0Input)
{
	
	ASSERT_EQ(fib(0), 0);	
}

TEST(FibTest1, Handles1Input)
{
	ASSERT_EQ(fib(1), 1);
}

TEST(FibTest2, Handles2Input)
{
	ASSERT_EQ(fib(2), 1);
}

TEST(FibTest3, Handles3Input)
{
	ASSERT_EQ(fib(3), 2);
}

TEST(FibTest4, Handles4Input)
{
	ASSERT_EQ(fib(4), 4);
}

TEST(FibTest5, Handles5Input)
{
	ASSERT_EQ(fib(5), 7);
}

TEST(FibTest6, HandlesNegInput)
{
	ASSERT_EQ(fib(-1), -1);
}

}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
