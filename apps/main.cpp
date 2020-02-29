

#include <iostream>
#include <stdexcept>


using namespace std;


void run();


int main( int argc, char* argv[] )
{

  try {
    run();
  }
  catch( exception& e ) {
    cerr << "std::exception hit--" << e.what() << "\n";
    return 1;
  }
  catch( ... ) {
    cerr << "unknown exception hit\n";
    return 2;
  }

  return 0;

}



void run()
{

  cout << "Welcome!\n";

}