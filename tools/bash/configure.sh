#!/usr/bin/env bash

###############################################################################
#
#
# \author  Travis Robson
###############################################################################



set -o errexit -o nounset -o pipefail


dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" /dev/null 2>&1 && pwd)"
root="$(cd ${dir}/../../ && pwd)"


cd ${root}


#
# Usage message
#
function usage()
{

  echo ""
  echo "configure.sh usage"
  echo "$ ./configure <options>"
  echo "--------------------------------------------------------------------------------"
  echo "  -gt, --google-test       build Google tests"
  echo "  -h,  --help              display this usage message"
  echo "  -i,  --install-prefix    installation prefix"
  echo "  -nw, --no-warnings       build without compiler warnings"
  echo "  -vb, --verbose-build     build commands will be displayed verbosely"
  echo ""

}


#
# Default options
# 
buildType="Debug"
installPrefix="${root}"
googleTest="OFF"
verboseBuild="OFF"
compilerWarnings="ON"


#
# Parse command line options
#
while [[ $# -gt 0 ]]; do

  key=$1
  
  case $key in

    -gt|--google-test)
    googleTest="ON"
    ;;

    -h|--help)
    usage
    exit 0
    ;;

    -i|--install-prefix)
    installPrefix=$2
    shift
    ;;

    -nw|--no-warnings)
    compilerWarnings="OFF"
    ;;

    -vb|--verbose-build)
    verboseBuild="ON"
    ;;

    *) # unknown argument
    echo "unrecognized option: $1"
    usage
    exit 1
    ;;

  esac

  shift

done



#
# construct CMake command
#
cmd="cmake"
cmd="${cmd} -G \"Unix Makefiles\""
cmd="${cmd} -DCMAKE_BUILD_TYPE=${buildType}"
cmd="${cmd} -DCMAKE_INSTALL_PREFIX=${installPrefix}"
cmd="${cmd} -DGOOGLE_TEST=${googleTest}"
cmd="${cmd} -DCMAKE_VERBOSE_MAKEFILE:BOOL=${verboseBuild}"
cmd="${cmd} -DCOMPILER_WARNINGS=${compilerWarnings}"
cmd="${cmd} .."


mkdir -p build 

cd build

eval "${cmd}"





