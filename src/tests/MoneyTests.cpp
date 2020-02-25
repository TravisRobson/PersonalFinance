

#include "MoneyTests.hpp"

#include "Money.hpp"


TEST( MoneyTests, OnePlusOneEqualsTwo )
{

  Money m1( 1, 00 );
  Money m2( 1, 00 );

  m1 += m2;

  ASSERT_EQ( m1, Money( 2, 00 ) );

  
}