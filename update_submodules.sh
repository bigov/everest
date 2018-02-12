#!/bin/sh
#
# Run only under Windows-MSYS2 or Linux native shell
#

if [[ `uname` =~ ^MINGW ]]; then
  echo ""
  echo "Please, call it from the MSYS, not using the MINGW shell!"
  exit
fi

git submodule init
git submodule update
cd 3rdparty/wxWidgets
git submodule init
git submodule update
cd ..
cd ..
