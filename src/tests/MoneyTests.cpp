

#include "MoneyTests.hpp"

#include <iostream>
#include <stdexcept>

#include "Money.hpp"


using namespace std;
using namespace pfin;


TEST( MoneyTests, OnePlusOneEqualsTwo )
{

  Money m1( 1, 00 );
  Money m2( 1, 00 );

  m1 += m2;

  ASSERT_EQ( m1, Money( 2, 00 ) );
  
}


TEST( MoneyTests, NegativeOnePlusNegativeOneEqualsTwo )
{

  Money m1( -1.00 );
  Money m2( -1.00 );

  m1 += m2;

  ASSERT_TRUE( m1 == Money( -2, -00 ) );
  
}


TEST( MoneyTests, OneFiftyPlusOneSixtyqualsThreeTen )
{

  Money m1( 1.50 );
  Money m2( 1.60 );

  m1 += m2;

  ASSERT_EQ( m1, Money( 3.10 ) );

}


TEST( MoneyTests, DollarsAndCentsSignsDifferThrow )
{

  ASSERT_THROW( Money m(  1, -10 ), runtime_error );

  ASSERT_THROW( Money m( -5,  20 ), runtime_error );

}

// \todo Do more of these, parameterized, to see that negative and edge cases are handled
TEST( MoneyTests, DoubleConstructorCorrect )
{

  Money m1( 1.03 );
  Money m2( 1,03 );

  ASSERT_EQ( m1, m2 );

}


TEST( MoneyTests, InequalityOperatorReturnsFalseWithEqualMoney )
{
  Money m1( 1.05 );
  Money m2( m1 );

  ASSERT_FALSE( m1 != m2 );

}


TEST( MoneyTest, OneMinusOneEqualsZero )
{

  Money m1( 1.00 );
  Money m2( 1.00 );

  m2 -= m1;

  ASSERT_TRUE( m2 == Money( 0.00 ) );

  Money m3 = m2 - m1;

  std::cout << m1 << "\n";
  std::cout << m2 << "\n";
  std::cout << m3 << "\n";

  ASSERT_TRUE( m3 == Money( 0.00 ) );

}


TEST( MoneyTest, DISABLED_NegativeOneMinusNegativeOneEqualsZero )
{

  Money m1( -1.00 );
  Money m2( -1.00 );

  Money m3 = m2 - m1; // - operator

  ASSERT_TRUE( m3 == Money( 0.00 ) );

  m2 -= m1; // -= operator

  ASSERT_TRUE( m2 == Money( 0.00 ) );

}



