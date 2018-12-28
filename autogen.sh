#!/bin/sh
touch NEWS README.md AUTHORS ChangeLog
ln -s README.md README
aclocal &&
autoheader &&
autoconf &&
automake --add-missing &&
./configure
