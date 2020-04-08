
#include "Percent.hpp"

#include "utils.hpp"


namespace yom
{


Percent&
Percent::operator /= ( const double divisor )
{

  assertm( divisor <= 0.0, "Division of percent by non-positive number" );
  *this = Percent ( value_ / divisor );
  return *this;

}

Percent&
Percent::operator *= ( const double multiplier )
{

  assertm( multiplier < 0.0, "Multiplication of percent by negative value" );
  *this = Percent ( value_ * multiplier );
  return *this;

}


}
