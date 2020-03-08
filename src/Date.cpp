

#include "personalFinance/Date.hpp"

#include <ctime>
#include <iostream> /// \todo remove when class is done


namespace fin {

///////////////////////////////////////////////////////////////////////////////
///
/// \precondition  day is between 1 - 31
/// 
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
Date::Date( Month month, unsigned int day, unsigned int year )
  : month_( month ),  day_( day ), year_( year )
{

  /// \todo asserts to validate arguments

  int tmMonth = static_cast< int >( month );
  int tmDay   = day;
  int tmYear  = year - 1900;

  tm time = tm {
    0,        // 0-60, seconds after the minute (60 is for leapseconds)
    0,        // 0-59, min after the hour
    0,        // 0-23, hours since midnight
    tmDay,    // 1-31, day of month
    tmMonth,  // 0-11, months since January
    tmYear    // years since 1900
  };

  timePoint_ = std::chrono::system_clock::from_time_t( mktime( &time ) );

}


Date::Date( std::chrono::system_clock::time_point timePoint )
  : timePoint_( timePoint )
{

  auto [ mo, dy, yr ] = timePointToDate( timePoint_ );
  month_ = mo;
  day_   = dy;
  year_  = yr;

}


///////////////////////////////////////////////////////////////////////////////
/// Date operators
///////////////////////////////////////////////////////////////////////////////
bool operator==( const Date& a, const Date& b )
{
  if ( a.month() != b.month() ) { return false; }
  if ( a.day()   != b.day()   ) { return false; }
  if ( a.year()  != b.year()  ) { return false; }

  return true;

}


bool operator!=( const Date& a, const Date& b )
{
  return !( a == b ); 
}


///////////////////////////////////////////////////////////////////////////////
/// \brief  Increment the date by one day
///////////////////////////////////////////////////////////////////////////////
Date& Date::operator++()
{

  timePoint_ += DAY;
  date_t date = timePointToDate( timePoint_ );
  *this       = Date( date.mo, date.dy, date.yr );

  return *this;

}


Date& Date::operator+=( unsigned int days )
{
  for ( int i = 0; i < days; ++i ) { ++*this; }
  return *this;
}


///////////////////////////////////////////////////////////////////////////////
/// Date utilities
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// \brief convert chrono's time_point to a month, day, and year
/// 
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
date_t timePointToDate( std::chrono::system_clock::time_point timePoint )
{

  auto time = std::chrono::system_clock::to_time_t( timePoint );

  // extract local time
  /// \todo do we want local or UTC? ( tm utcTime = *gmtime( time ); )
  tm localTime = *localtime( &time );

  Month        month = Month( localTime.tm_mon );                               // tm_month [0,11]
  unsigned int day   = static_cast< unsigned int >( localTime.tm_mday );        
  unsigned int year  = static_cast< unsigned int >( localTime.tm_year + 1900 ); // tm_year is since 1900

  return date_t{ month, day, year };

}



Date DateToday()
{

  auto now  = std::chrono::system_clock::now();

  auto [ mo, dy, yr ] = timePointToDate( now );

  return Date( mo, dy, yr );

}


}

