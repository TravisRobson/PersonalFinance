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


rm -rf build lib bin 