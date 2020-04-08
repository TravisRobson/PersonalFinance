

#ifndef Loan_hpp
#define Loan_hpp


#include "Money.hpp"
#include "Percent.hpp


///////////////////////////////////////////////////////////////////////////////
/// \brief  Loans, i.e. a principal and interest rate
///
/// This class does not assume any policy for applying the loan
///
///////////////////////////////////////////////////////////////////////////////
class Loan
{

public:
  
  Loan( Money principal, Percent monthlyInterest ) // I've chosen 
    : principal_( principal ), monthlyInterest_( monthlyInterest ) {}
    
  Money principal() const         { return principal_; }
  Percent monthlyInterest() const { return monthlyInterest_; }
  Percent yearlyInterest() const  { return monthlyInterest_ * 12.0; }
    
private:
  
  Money   principal_;
  Percent monthlyInterest_;
    
};

#endif

