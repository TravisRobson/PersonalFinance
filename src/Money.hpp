

#ifndef Money_hpp
#define Money_hpp


#include <string>


using namespace std;


///////////////////////////////////////////////////////////////////////////////
/// \brief  Class to represent money. It can represent negative money.
///
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
class Money
{

public:

  Money( string amount );
  Money( int dollars, int cents );

  Money& operator+=( const Money& money );
  //Money operator+( const Money& money );

  int dollars() const { return dollars_; }
  int cents()   const { return cents_;   }


private:

  int dollars_;
  int cents_;


};



#endif