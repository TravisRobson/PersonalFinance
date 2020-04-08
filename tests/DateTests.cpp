

#include <chrono>
#include <ctime>
#include <iostream>

#include "personalFinance/Date.hpp"

#include "gtest/gtest.h"


using namespace yom;


TEST( DateTests, TodaysDate )
{

  Date date = DateToday();
  std::cout << monthToString[ date.month() ] << " " << date.day() << ", " << date.year() << "\n";

}
