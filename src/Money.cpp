

#include "Money.hpp"

#include <string>

using namespace std;


Money::Money( string amount )
{

}


Money::Money( int dollars, int cents )
  : dollars_( dollars ), cents_( cents )
{}


Money& Money::operator+=( const Money& money )
{

  dollars_ += money.dollars();
  cents_   += money.cents();

  return *this;

}



// Money Money::operator+( const Money& money )
// {

//   dollars_ += money.dollars();
//   cents_   += money.cents();

// }