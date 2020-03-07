#include <gtest/gtest.h>

#include <gtest/gtest.h>

TEST( SanityCheckTests, ZeroEqZero )
{
	EXPECT_EQ( 0, 0 );
}

TEST( SanityCheckTests, OneEqOne )
{
	EXPECT_EQ( 1, 1 );
}

TEST( SanityCheckTests, ZeroNeOne )
{
	EXPECT_NE( 0, 1 );
}

TEST( SanityCheckTests, TrueIsTrue )
{
	EXPECT_TRUE( true );
}

TEST( SanityCheckTests, FalseIsFalse )
{
	EXPECT_FALSE( false );
}

TEST( SanityCheckTests, TrueNeFalse )
{
	EXPECT_NE( true, false );
}
