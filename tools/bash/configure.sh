###############################################################################
#
#
# \author  Travis Robson
###############################################################################
#!/usr/bin/env bash


set -o errexit -o nounset -o pipefail


dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" /dev/null 2>&1 && pwd)"
root="$(cd ${dir}/../../ && pwd)"


cd ${root}


#
# Usage message
#



#
# Default options
# 
buildType="Debug"
installPrefix="${root}"


#
# Parse command line options
#




#
# construct CMake command
#
cmd="cmake"
cmd="${cmd} -G \"Unix Makefiles\""
cmd="${cmd} -DCMAKE_BUILD_TYPE=${buildType}"
cmd="${cmd} -DCMAKE_INSTALL_PREFIX=${installPrefix}"
cmd="${cmd} .."


mkdir -p build lib bin

cd build

eval "${cmd}"





