#!/bin/bash

# todo: check if robot plugins are compiled

#dir check
if [ -d ~/.lv2 ]; then
    echo "lv2 directory exist" ;
else
    echo "creating ~/.lv2" ;
    mkdir ~/.lv2 ;
fi

if [ -d ~/.vst ]; then
    echo "vst directory exist" ;
else
    echo "creating ~/.vst" ;
    mkdir ~/.vst ;
fi

if [ -d ~/.dssi ]; then
    echo "dssi directory exist" ;
else
    echo "creating ~/.dssi" ;
    mkdir ~/.dssi ;
fi

if [ -d ~/.ladspa ]; then
    echo "ladspa directory exist" ;
else
    echo "creating ~/.ladspa" ;
    mkdir ~/.ladspa ;
fi

# TVDistortion
rm -fr ~/.lv2/TVDistortion.lv2 ;
mkdir ~/.lv2/TVDistortion.lv2 ;

cp -f bin/TVDistortion-vst.so ~/.vst/ ;
cp -f bin/TVDistortion-dssi.so ~/.dssi/ ;
cp -fa bin/TVDistortion-dssi ~/.dssi/ ;
cp -f bin/TVDistortion.lv2/* ~/.lv2/TVDistortion.lv2/ ;

# Rainbow
rm -fr ~/.lv2/Rainbow.lv2 ;
mkdir ~/.lv2/Rainbow.lv2 ;

cp -f bin/Rainbow-ladspa.so ~/.ladspa/ ;
cp -f bin/Rainbow-vst.so ~/.vst/ ;
cp -f bin/Rainbow-dssi.so ~/.dssi/ ;
cp -fa bin/Rainbow-dssi ~/.dssi/ ;
cp -f bin/Rainbow.lv2/* ~/.lv2/Rainbow.lv2/ ;

# CreamWhipper

rm -fr ~/.lv2/CreamWhipper.lv2 ;
mkdir ~/.lv2/CreamWhipper.lv2 ;

cp -f bin/CreamWhipper-ladspa.so ~/.ladspa/ ;
cp -f bin/CreamWhipper-vst.so ~/.vst/ ;
cp -f bin/CreamWhipper-dssi.so ~/.dssi/ ;
cp -fa bin/CreamWhipper-dssi ~/.dssi/ ;
cp -f bin/CreamWhipper.lv2/* ~/.lv2/CreamWhipper.lv2/ ;

# RandomMIDIcc
rm -fr ~/.lv2/RandomMIDIcc.lv2 ;
mkdir ~/.lv2/RandomMIDIcc.lv2 ;

cp -f bin/RandomMIDIcc-vst.so ~/.vst/ ;
cp -f bin/RandomMIDIcc.lv2/* ~/.lv2/RandomMIDIcc.lv2/ ;

echo "Installed/Updated"
echo "You're Momma!!"
