

#ifndef Percentage_hpp
#define Percentage_hpp


namespace yom {
  

///////////////////////////////////////////////////////////////////////////////
/// \brief  percent--number expressed as fraction of 100
///
/// This class is intended to avoid confusion between ratio and percentages
/// in calculations, i.e. 0.03 vs 3%.
/// 
///////////////////////////////////////////////////////////////////////////////
class Percent
{

public:
    
  Percent( double percent )
    : value_( percent ) {}
  
  double operator() const { return value_; }
  
  Percent& operator /=( const double divisor    );
  Percent& operator *=( const double multiplier );
    
private:

  double value_;
  
};


}


#endif