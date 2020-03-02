

#include "main.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "personalFinance/config.hpp"
#include "personalFinance/Money.hpp"


using std::cout;
using std::cerr;


///////////////////////////////////////////////////////////////////////////////
/// \brief  A work in progress demo
///
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{

  try {
    run( argc, argv );
  }
  catch( std::exception& e ) {
    cerr << "std::exception hit--" << e.what() << "\n";
    return 1;
  }
  catch( ... ) {
    cerr << "unknown exception hit\n";
    return 2;
  }

  return 0;

}


void run( int argc, char* argv[] )
{

  cout << "Welcome!\n";
  parseCommandLineArgs( argc, argv );

  fin::Money m( 1.00 );
  std::cout << "Money--$" << m << "\n";

}


///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \author  Travis Robson
///////////////////////////////////////////////////////////////////////////////
void parseCommandLineArgs( int argc, char* argv[] )
{

  while( true ) {

    int longOptIndex{ 0 };

    const auto returnValue = getopt_long( argc, argv, shortOptions_, longOptions_, &longOptIndex );

    if ( returnValue == endOfOptions_ ) { break; }

    switch( returnValue ) {

      case 0:
        throw std::runtime_error( "parseCommandLineArgs, flag setting option was detected, but none were used" );
        break;

      case 'c': // --config-file
        configFilename_ = std::string( optarg );
        break;

      case 'h': // --help
        printUsage();
        std::exit( 0 ); /// \todo is there a cleaner way to do this?
        break;

      case 'n': // --no-gui
        break;

      case 'v': // --version

        cout << "PersonalFinance version: v";
        cout << PERSONALFINANCE_MAJOR_VERSION << ".";
        cout << PERSONALFINANCE_MINOR_VERSION << ".";
        cout << PERSONALFINANCE_PATCH_VERSION << "\n";
        std::exit( 0 ); /// \todo is there a cleaner way to do this?
        break;

      case '?': // unrecognized options
        throw std::runtime_error( "unrecognized option: " + std::string( optarg ) );
        break;

      case ':': // missing argument
        if ( optopt == 'c' ) {
          cerr << "option: -" << (char)optopt << ", --" << longOptions_[ longOptIndex ].name << ". ";
          cerr << "Using default config file: " << configFilename_ << "\n";
        }
        break;

      default:
        throw std::runtime_error( "hit default command line options case" );
        break;

    }

  }

  // check for any remaining, unused things passes via command line
  if ( optind < argc ) {

    cerr << "non-option argv elements: ";
    while( optind < argc ) {
      cerr << argv[ optind++ ] << " ";
    }
    cerr << "\n";

  }

}


void printUsage()
{

  cout << "Usage:\n";
  cout << "$ ./bin/main <options>\n\n";
  cout << "-c, --config-file <filename>      Set the configuration file.\n";
  cout << "-h, --help                        Show this usage message.\n";
  cout << "-n, --no-gui                      No gui mode.\n";
  cout << "\n";

}









