

#ifndef Date_hpp
#define Date_hpp


#include <chrono>
#include <map>
#include <ostream>
#include <string>


namespace fin {


enum class Month {
  January,   February, March,    April,
  May,       June,     July,     August,
  September, October,  November, December
};

std::map< Month, std::string > monthToString {
  { Month::January,   "January"   },
  { Month::February,  "February"  },
  { Month::March,     "March"     },
  { Month::April,     "April"     },
  { Month::May,       "May"       },
  { Month::June,      "June"      },
  { Month::July,      "July"      },
  { Month::August,    "August"    },
  { Month::September, "September" },
  { Month::October,   "October"   },
  { Month::November,  "November"  },
  { Month::December,  "December"  }
};

/// \todo I don't know if I want this, probably want to let time_point handle this operation...
Month& operator++( Month& m ) {
  switch( m ) {
    case Month::January:   return m = Month::February;
    case Month::February:  return m = Month::March;
    case Month::March:     return m = Month::April;
    case Month::April:     return m = Month::May;
    case Month::May:       return m = Month::June;
    case Month::June:      return m = Month::July;
    case Month::July:      return m = Month::August;
    case Month::August:    return m = Month::September;
    case Month::September: return m = Month::October;
    case Month::October:   return m = Month::November;
    case Month::November:  return m = Month::December;
    case Month::December:  return m = Month::January;
  }
}


///////////////////////////////////////////////////////////////////////////////
///
/// \todo should day and year be simple class or something?
///
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
class Date
{

public:

  Date( Month month, unsigned int day, unsigned int year );
  Date( std::chrono::system_clock::time_point );

  unsigned int day()   const { return day_;   }
  Month        month() const { return month_; }
  unsigned int year()  const { return year_;  }

  Date& operator++();
  Date operator++( int ) {
    Date tmp = *this;
    ++*this;
    return tmp;
  }
  Date& operator+=( unsigned int days );

  friend std::ostream& operator<<( std::ostream& os, const Date& date );

private:

  Month        month_;
  unsigned int day_;
  unsigned int year_;

  std::chrono::system_clock::time_point timePoint_;

  static constexpr std::chrono::hours DAY{ std::chrono::hours( 24 ) };

};


bool operator==( const Date&, const Date& );
bool operator!=( const Date&, const Date& );

std::ostream& operator<<( std::ostream& os, const Date& date )
{
  // os.imbue( locale( "en_US.utf8" ) ); /// \todo This fails for some reason. OSX issue?
  os << monthToString[ date.month() ] << " ";
  os << date.day() << ", " << date.year();

  return os;

}

// utility functions
struct date_t { /// a simple package of the things defining the date
  Month        mo;
  unsigned int dy;
  unsigned int yr;
};
date_t timePointToDate( std::chrono::system_clock::time_point );
Date DateToday();



}


#endif
