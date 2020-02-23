#!/usr/bin/env bash

###############################################################################
#
#
# \author  Travis Robson
###############################################################################



set -o errexit -o nounset -o pipefail


dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" /dev/null 2>&1 && pwd)"
root="$(cd ${dir}/../.. && pwd)"

echo ${dir}
ls ${dir}/utils.shlib
source ${dir}/utils.shlib
cd ${root}

# ensure that the build directory has been built, i.e. build has been configured
if [[ ! -d build ]]; then

  printf "$(red)$(bold)build/ directory does not exist. Be sure to run configure.sh$(reset)\n"
  exit 1

fi

cmake --build build -j


