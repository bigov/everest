#!/bin/sh
#
# On certain platforms (e.g. Linux) you'll now have to run ldconfig
# if you installed a shared library and also modify the LD_LIBRARY_PATH
# (or equivalent) environment variable.
#

if [[ `uname` =~ ^MSYS_NT ]]; then
  echo ""
  echo "Do not using the MSYS!"
  echo "Please, call it from the MinGW!"
  exit
fi

SRC_DIR=`pwd`
DEST="${SRC_DIR}/3rdparty/staticlib"

OPTIONS="--disable-debug --enable-cxx11 --disable-shared --enable-utf8only\
 --disable-compat30 --with-libjpeg=builtin --with-libpng=builtin\
 --with-regex=builtin --with-libtiff=builtin --with-zlib=builtin\
 --with-expat=builtin"

mkdir ${DEST}
cd ${DEST}
../wxWidgets/configure ${OPTIONS} --prefix=${DEST} --exec-prefix=${DEST}/../tmp
make && make install && make clean
cp -fr ../tmp/* ./
cd ..
rm -rf tmp
cd wxWidgets
git checkout -- '*'
cd ..
cd ..
