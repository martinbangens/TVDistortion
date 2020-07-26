#!/bin/sh

# TVDistortion
rm -fr ~/.lv2/TVDistortion.lv2
mkdir ~/.lv2/TVDistortion.lv2

cp -f  bin/TVDistortion-vst.so ~/.vst/ ;
cp -f  bin/TVDistortion-dssi.so ~/.dssi/ ;
cp -f  bin/TVDistortion-dssi/TVDistortion_ui ~/.dssi/TVDistortion-dssi/ ;
cp -f bin/TVDistortion.lv2/* ~/.lv2/TVDistortion.lv2/ ;

# DigitalGain
rm -fr ~/.lv2/DigitalGain.lv2
mkdir ~/.lv2/DigitalGain.lv2

cp -f  bin/DigitalGain-ladspa.so ~/.ladspa/ ;
cp -f  bin/DigitalGain-vst.so ~/.vst/ ;
cp -f  bin/DigitalGain-dssi.so ~/.dssi/ ;
cp -f  bin/DigitalGain-dssi/DigitalGain_ui ~/.dssi/DigitalGain-dssi/ ;
cp -f bin/DigitalGain.lv2/* ~/.lv2/DigitalGain.lv2/ ;

# RandomMIDIcc
rm -fr ~/.lv2/RandomMIDIcc.lv2
mkdir ~/.lv2/RandomMIDIcc.lv2

cp -f  bin/RandomMIDIcc-vst.so ~/.vst/ ;
cp -f bin/RandomMIDIcc.lv2/* ~/.lv2/RandomMIDIcc.lv2/ ;
