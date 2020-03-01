

#ifndef main_hpp
#define main_hpp


#include <getopt.h>
#include <string>


void run( int argc, char* argv[] );
void parseCommandLineArgs( int argc, char* argv[] );
void printUsage();


// getopt.h data
const char* const shortOptions_ = ":c:hn"; // first ':' is so that we can handle failure to provide a required_argument
const option longOptions_[] = {
  { "config-file", required_argument, nullptr, 'c' },
  { "help",        no_argument,       nullptr, 'h' },
  { "no-gui",      no_argument,       nullptr, 'n' },
  { nullptr,       no_argument,       nullptr,  0  }
};
const int endOfOptions_{ -1 };


std::string configFilename_{ "etc/defaultConfig.yaml" };


#endif