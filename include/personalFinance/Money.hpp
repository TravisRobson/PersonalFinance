

#ifndef Money_hpp
#define Money_hpp


#include <iostream>


using std::ostream;


namespace yom {


///////////////////////////////////////////////////////////////////////////////
/// \brief  Class to represent money. It can represent negative money.
///
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
class Money
{

  int dollars_, cents_;

public:

  Money() : dollars_( 0 ), cents_( 0 ) {}
  Money( double amount );
  Money( int dollars, int cents );

  int dollars() const { return dollars_; }
  int cents()   const { return cents_;   }
  double toDouble() const { /// \todo I feel like this is a risky function to expose
    return dollars_ + 1.0 * cents_ / centsInDollar;
  }

  Money& operator+=( const Money& money );
  Money& operator-=( const Money& money );
  Money& operator *=( const double multiplier );
  Money& operator /=( const double divisor    );

  friend ostream& operator<<( ostream& os, const Money& money );

private:

  static constexpr int centsInDollar { 100 };
  void rollOverCents();


};


ostream& operator<<( ostream& os, const Money& money )
{

  // os.imbue( locale( "en_US.utf8" ) ); /// \todo This fails for some reason. OSX issue?

  if ( money.dollars() < 0.0 ) { os << "-"; }
  os << abs( money.dollars() ) << ".";

  if ( abs( money.cents()  ) < 10 ) { os << "0"; }
  os << abs( money.cents() );

  return os;

}

// comparison operators
bool operator==( const Money& a, const Money& b );
bool operator!=( const Money& a, const Money& b );
bool operator< ( const Money& a, const Money& b );
bool operator> ( const Money& a, const Money& b );
bool operator<=( const Money& a, const Money& b );
bool operator>=( const Money& a, const Money& b );


Money operator+( Money a, Money b ) { return a+=b; }
Money operator-( Money a, Money b ) { return a-=b; }
Money operator-( Money a ) { return { -a.dollars(), -a.cents() }; }

}


#endif

