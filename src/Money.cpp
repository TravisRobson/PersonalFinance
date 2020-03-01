
/// \todo there is like a 95% chance that I made this class too convoluted
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

  assert( ( ( dollars >= 0 && cents >= 0 ) || ( dollars <= 0 && cents <= 0 )  ) && "Dollars and cents must be of the same sign." );

}


/// \todo seems more complicated than necessary
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


bool operator==( const Money& a, const Money& b )
{

  bool dollarsEqual = ( a.dollars() == a.dollars() );
  bool centsEqual   = ( a.cents()   == b.cents()   );

  if ( dollarsEqual && centsEqual ) { return true; }
  else { return false; }

}

bool operator!=( const Money& a, const Money& b )
{
  return !( a == b );
}


bool operator<( const Money& a, const Money& b )
{

  double aTotal{ a.toDouble() };
  double bTotal{ b.toDouble() };

  if ( aTotal < bTotal ) { return true; }
  else { return false; }

}


bool operator>( const Money& a, const Money& b )
{

  double aTotal{ a.toDouble() };
  double bTotal{ b.toDouble() };

  if ( aTotal > bTotal ) { return true; }
  else { return false; }

}


bool operator<=( const Money& a, const Money& b )
{

  return ( ( a < b ) || ( a == b ) );

}


bool operator>=( const Money& a, const Money& b )
{

  return ( ( a > b ) || ( a == b ) );

}




Money& Money::operator+=( const Money& money )
{

  dollars_ += money.dollars();
  cents_   += money.cents();

  rollOverCents();

  return *this;

}


/// \todo seems more complicated than necessary

void Money::rollOverCents()
{

  bool centsGreaterThanDollar = ( abs( cents_ ) >= centsInDollar );

  if ( centsGreaterThanDollar ) {

    if ( cents_ >= 0 || dollars_ >= 0 ) {

      dollars_ += 1;
      cents_   -= centsInDollar;

    }
    else {

      dollars_ -= 1;
      cents_   += centsInDollar;   

    }

  }

}


Money& Money::operator-=( const Money& money )
{

  Money negate( -money.dollars(), -money.cents() );
  *this += negate;

  return *this;

}


Money& Money::operator*=( const double multiplier )
{

  cents_   *= multiplier;
  dollars_ *= multiplier;

  rollOverCents();

  return *this;

}


Money& Money::operator/=( const double divisor )
{

  double cents   = cents_;
  double dollars = dollars_;

  double amount  = dollars_ + cents / centsInDollar ;

  amount /= divisor;

  *this = Money( amount );

  return  *this;

}





}


