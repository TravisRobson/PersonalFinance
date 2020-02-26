

#ifndef Money_hpp
#define Money_hpp


#include <iostream>


using namespace std;


///////////////////////////////////////////////////////////////////////////////
/// \brief  Class to represent money. It can represent negative money.
///
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
class Money
{

public:

  Money( double amount );
  Money( int dollars, int cents );


  Money& operator+=( const Money& money );
  Money  operator+( const Money& money ) const;

  bool operator==( const Money& rhs ) const;

  int dollars() const { return dollars_; }
  int cents()   const { return cents_;   }

  friend ostream& operator<<( ostream& os, const Money& money );


private:

  int dollars_;
  int cents_;

  static constexpr int centsInDollar { 100 };


};


ostream& operator<<( ostream& os, const Money& money )
{

  if ( money.dollars() < 0.0 ) { os << "-"; }

  os << money.dollars() << ".";

  if ( money.cents() < 10 ) { os << "0"; }
    
  os << money.cents();

  return os;

}



#endif