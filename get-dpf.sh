#!/bin/bash

echo "This script is not tested hit control c"
read

set -e



if [ ! -f Makefile ]; then
  echo "Makefile not found, please run this script from DistoTV root source dir"
  exit
fi

rm -rf repos
mkdir repos
cd repos

git clone --depth 1 git://github.com/DISTRHO/DPF



cd ..

rm -rf dpf
rm -rf modguis


mv repos/DPF dpf
rm -rf dpf/.git*
rm -rf dpf/.travis*
rm -rf dpf/examples
rm -f  dpf/Makefile



rm -rf repos

