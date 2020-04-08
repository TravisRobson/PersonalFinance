

#include "MoneyTests.hpp"

#include <iostream>
#include <stdexcept>


using namespace std;
using namespace yom;


///////////////////////////////////////////////////////////////////////////////
/// \brief  Make sure that initialization list behaves as expected
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, InitialzationList )
{

  Money m{ 1, 42 };
  ASSERT_EQ( m, Money( 1.42 ) );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief  Make sure that human readable constructor that takes a double 
/// works
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, DoubleConstructorCorrect )
{

  // positive money
  m1_ = Money( 1.03 );
  m2_ = Money( 1,03 );

  ASSERT_EQ( m1_, m2_ );

  // negative money
  m1_ = Money( -1.54 );
  m2_ = Money( -1, -54 );

  ASSERT_EQ( m1_, m2_ );

}


TEST_F( MoneyTests, FractionalMultiplier )
{

  m1_ = Money( 1.00 );
  m1_ *= 0.5;

  ASSERT_EQ( m1_, Money( 0.50 ) );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief check that equality operator works
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, EqualityOperator )
{

  m1_ = Money( 1.04 );
  m2_ = Money( 1.04 );

  ASSERT_EQ( m1_, m2_ );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief check that inequality operator works
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, InequalityOperator )
{

  m1_ = Money( 1.04 );
  m2_ = Money( 1.05 );

  ASSERT_NE( m1_, m2_ );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief check that += operator works for one plus one
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, OnePlusOneEqualsTwo )
{

  m1_ = Money( 1, 00 );
  m2_ = Money( 1, 00 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( 2.00 ) );
  
}


///////////////////////////////////////////////////////////////////////////////
/// \brief check that += operator works for -one plus -one
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, NegativeOnePlusNegativeOneEqualsNegativeTwo )
{

  m1_ = Money( -1.00 );
  m2_ = Money( -1.00 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( -2.00 ) );
  
}


///////////////////////////////////////////////////////////////////////////////
/// \brief check that += operator works when change "rolls over", i.e.
/// 1.30 + 1.80 = 3.10
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, PlusEqualsOperatorRollOver )
{

  m1_ = Money( 1.30 );
  m2_ = Money( 1.80 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( 3.10 ) );


  m1_ = Money( 1.50 );
  m2_ = Money( 1.50 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( 3.00 ) );

}

///////////////////////////////////////////////////////////////////////////////
/// \brief check that += operator works when change "rolls over", i.e.
/// -1.30 + -1.80 = -3.10
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, PlusEqualsOperatorRollOverWhenBothNegative )
{

  m1_ = Money( -1.30 );
  m2_ = Money( -1.80 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( -3.10 ) );


  m1_ = Money( -1.50 );
  m2_ = Money( -1.50 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( -3.00 ) );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, MixedMoneySignsPlusEqualsOperator )
{

  m1_ = Money( -1.30 );
  m2_ = Money(  1.80 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( 0.50 ) );

  m1_ = Money(  1.50 );
  m2_ = Money( -3.50 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( -2.00 ) );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, OnePlusNegativeOneEqualsZero )
{

  m1_ = Money(  1.00 );
  m2_ = Money( -1.00 );

  m1_ += m2_;

  ASSERT_EQ( m1_, Money( 0.00 ) );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, OneMinusOneEqualZero )
{

  m1_ = Money( 1.00 );
  m2_ = Money( 1.00 );

  m1_ -= m2_;

  ASSERT_EQ( m1_, Money( 0.00 ) );  

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, MultipiesEqualsOperator )
{

  m1_ = Money( 1.45 );
  m1_ *= 2;

  ASSERT_EQ( m1_, Money( 1.90 ) );

  m1_ = Money( 1.45 );
  m1_ *= -2;

  ASSERT_EQ( m1_, Money( -1.90 ) );

  m1_ = Money( 1.55 );
  m1_ *= -2;

  ASSERT_EQ( m1_, Money( -2.10 ) );

  m1_ = Money( 1.55 );
  m1_ *= 2;

  ASSERT_EQ( m1_, Money( 2.10 ) );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, DividesEqualsOperatorEvenDollarsEvenCents )
{

  m1_ = Money( 2.50 ); 
  m1_ /= 2;

  ASSERT_EQ( m1_, Money( 1.25 ) );

  m1_ = Money( 2.50 ); 
  m1_ /= -2;

  ASSERT_EQ( m1_, Money( -1.25 ) );

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, DividesEqualsOperatorEvenDollarsOddCents )
{

  // an even amount of dollars and odd amount of cents
  m1_ = Money( 2.45 ); 
  m1_ /= 2;

  ASSERT_EQ( m1_, Money( 1.23 ) ); /// we have chosen to obey rounding

  m1_ = Money( 2.45 ); 
  m1_ /= -2;

  ASSERT_EQ( m1_, Money( -1.23 ) ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, DividesEqualsOperatorOddDollarsEvenCents )
{

  m1_ = Money( 3.50 ); 
  m1_ /= 2;

  ASSERT_EQ( m1_, Money( 1.75 ) ); 

  m1_ = Money( 3.50 ); 
  m1_ /= -2;

  ASSERT_EQ( m1_, Money( -1.75 ) ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, DividesEqualsOperatorOddDollarsOddCents )
{

  m1_ = Money( 3.45 ); 
  m1_ /= 2;

  ASSERT_EQ( m1_, Money( 1.73 ) ); 

  m1_= Money( 3.45 ); 
  m1_ /= -2;

  ASSERT_EQ( m1_, Money( -1.73 ) ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, LessThanOperator )
{

  m1_ = Money( 1.23 ); 
  m2_ = Money( 1.00 );

  ASSERT_LT( m2_, m1_ ); 

  m1_ = Money( -1.23 ); 
  m2_ = Money( -1.00 );

  ASSERT_LT( m1_, m2_ ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, GreaterThanOperator )
{

  m1_ = Money( 1.23 ); 
  m2_ = Money( 1.00 );

  ASSERT_GT( m1_, m2_ ); 

  m1_ = Money( -1.23 ); 
  m2_ = Money( -1.00 );

  ASSERT_GT( m2_, m1_ ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, LessThanEqualsOperator )
{

  m1_ = Money( 1.23 ); 
  m2_ = Money( 1.00 );

  ASSERT_LE( m2_, m1_ ); 

  m1_ = Money( -1.23 ); 
  m2_ = Money( -1.00 );

  ASSERT_LE( m1_, m2_ ); 


  m1_ = Money( -1.00 ); 
  m2_ = Money( -1.00 );

  ASSERT_GE( m2_, m1_ ); 

  m1_ = Money( 1.00 ); 
  m2_ = Money( 1.00 );

  ASSERT_GE( m2_, m1_ ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief 
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, GreaterThanEqualsOperator )
{

  m1_ = Money( 1.23 ); 
  m2_ = Money( 1.00 );

  ASSERT_GE( m1_, m2_ ); 

  m1_ = Money( -1.23 ); 
  m2_ = Money( -1.00 );

  ASSERT_GE( m2_, m1_ ); 

  m1_ = Money( -1.00 ); 
  m2_ = Money( -1.00 );

  ASSERT_GE( m2_, m1_ ); 

  m1_ = Money( 1.00 ); 
  m2_ = Money( 1.00 );

  ASSERT_GE( m2_, m1_ ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief  test addition operator, not +=
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, OnePlusTwoEqualsThree )
{

  m1_ = Money( 1.00 ); 
  m2_ = Money( 2.00 );

  Money m3 = m1_ + m2_;

  ASSERT_GE( m3, Money( 3.00 ) ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief  test subtraction operator, not -=
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, OneMinusTwoEqualsNegativeOne )
{

  m1_ = Money( 1.00 ); 
  m2_ = Money( 2.00 );

  Money m3 = m1_ - m2_;

  ASSERT_GE( m3, Money( -1.00 ) ); 

}


///////////////////////////////////////////////////////////////////////////////
/// \brief  unary - operator
///////////////////////////////////////////////////////////////////////////////
TEST_F( MoneyTests, NegateOneEqualsNegativeOne )
{

  m1_ = -Money( 1.00 ); 

  ASSERT_GE( m1_, Money( -1.00 ) ); 

}


