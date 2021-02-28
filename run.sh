#!/bin/bash
bin/TVDistortion &
sleep 3;
jack_connect "TVDistortion:out1" "Calf Studio Gear:Analyzer In #1";
jack_connect "TVDistortion:out2" "Calf Studio Gear:Analyzer In #2";
jack_connect "zynaddsubfx:out_1" "TVDistortion:in1";
jack_connect "zynaddsubfx:out_2" "TVDistortion:in2";

