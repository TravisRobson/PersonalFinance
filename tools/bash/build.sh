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


# ensure that the build directory has been built, i.e. build has been configured
if [[ ! -d build ]]; then

  exit 1

fi

cmake --build build -j


