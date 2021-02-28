#!/bin/bash


make clean


set -e



if [ ! -f Makefile ]; then
  echo "Makefile not found, please run this script from robot root source dir"
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
rm -f  dpf/Makefile dpf/dpf.kdev4



rm -rf repos

