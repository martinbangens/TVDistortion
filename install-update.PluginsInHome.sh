#!/bin/sh

rm -fr ~/.lv2/TVDistortion.lv2
mkdir ~/.lv2/TVDistortion.lv2

cp -f  bin/TVDistortion-vst.so ~/.vst/ ;
cp -f  bin/TVDistortion-dssi.so ~/.dssi/ ;
cp -f  bin/TVDistortion-dssi/TVDistortion_ui ~/.dssi/TVDistortion-dssi/ ;
cp -f bin/TVDistortion.lv2/* ~/.lv2/TVDistortion.lv2/ ;
