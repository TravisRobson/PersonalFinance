

#ifndef MoneyTests_hpp
#define MoneyTests_hpp


#include "personalFinance/Money.hpp"

#include "gtest/gtest.h"


using namespace yom;


///////////////////////////////////////////////////////////////////////////////
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
class MoneyTests
  : public ::testing::Test
{

protected:

  MoneyTests() {}
  ~MoneyTests() {}

  Money m1_;
  Money m2_;

};

#endif