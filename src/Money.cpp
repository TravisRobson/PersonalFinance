

#include "Money.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>


using namespace std;


namespace pfin {


///////////////////////////////////////////////////////////////////////////////
/// \brief  The basic money constructor
///
/// Constructor assumes dollars and cents are of the same sign, otherwise 
/// throws.
///
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
Money::Money( int dollars, int cents )
  : dollars_( dollars ), cents_( cents )
{

  /// \todo How to handle dollars or cents being zero. We would prefer not to put a minux sign on a zero
  assert( ( dollars < 0 && cents > 0 ) && "Dollars and cents must be of the same sign." );
  assert( ( dollars > 0 && cents < 0 ) && "Dollars and cents must be of the same sign." );

}


Money::Money( double amount )
  : dollars_( 0 ), cents_( 0 )
{

  bool positive = ( amount > 0.0 );

  amount = abs( amount );

  double fractionOfDollar = amount - floor( amount );
  fractionOfDollar        = round( centsInDollar * fractionOfDollar ); // e.g. $0.305 * 100 = 30.5 --> 31 
  int cents               = static_cast< int >( fractionOfDollar );
  int dollars             = static_cast< int >( amount - 1.0 * cents / centsInDollar );

  if ( !positive ) {

    cents   *= -1;
    dollars *= -1;

  }

  new (this) Money( dollars, cents );

}


Money& Money::operator+=( const Money& money )
{

  dollars_ += money.dollars();
  cents_   += money.cents();

  bool centsGreaterThanDollar = ( cents_ > centsInDollar );
  if ( centsGreaterThanDollar ) {
    dollars_ += 1;
    cents_   -= centsInDollar;
  }

  return *this;

}


Money Money::operator+( const Money& money ) const
{


  Money m( *this );
  m += money;

  return money;

}


Money& Money::operator-=( const Money& money )
{

  std::cout << *this << "\n";

  dollars_ -= money.dollars();
  cents_   -= money.cents();

  std::cout << *this << "\n";

  bool centsGreaterThanDollar = ( cents_ > centsInDollar );
  if ( centsGreaterThanDollar ) {
    dollars_ += 1;
    cents_   -= centsInDollar;
  }

  return *this;

}


Money Money::operator-( const Money& money ) const
{

  Money m( *this );
  m -= money;

  std::cout << "dollars: " << m << "\n";

  return money;

}


bool Money::operator==( const Money& rhs ) const
{

  bool dollarsEqual = dollars() == rhs.dollars();
  bool centsEqual   = cents() == rhs.cents();

  if ( dollarsEqual == centsEqual ) { return true; }
  else { return false; }

}


}


