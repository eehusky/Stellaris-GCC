TIStellarisBuild
================

Scripts to Build TI Stellaris ARM Toolchain, Libraries, and Programs using GCC.

##How-To:
1. Download and build the Summon Arm Toolchain from [here][sat]
2. Download and build lm4flash tools from [here][lm4]
3. Download and extract the Stellaris Ware package from [here][sw]

4. Clone this repo
5. Change line 17 of the Makefile to point to the root of your Summon Arm Toolchain directory (note: root, not bin/)

    TOOL        = /mnt/raidarray/share/workspace/sat/

6. Change the following line to point to the root of the Stellaris Ware directory.

    SW_DIR      = /mnt/raidarray/share/workspace/embedded/stellaris/sw/

7. I moved the lm4flash binaries to the bin directory of the gcc toolchain so `$(TOOL)/bin/lm4flash` simply to keep everything in the same spot.  If you dont want to, youll need to change the path on line 93.

    FLASH       = $(TOOL)/bin/lm4flash

8. Assuming everything went alright, you should be able to `cd proj0 && make && make install` to flash the provided progrom to the board.




[sat]:   https://github.com/esden/summon-arm-toolchain  "summon-arm-toolchain"
[lm4]:   https://github.com/utzig/lm4tools "lm4tools"
[sw]:    http://www.ti.com/tool/sw-ek-lm4f120xl "Stellaris Ware Download, pn: SW-EK-LM4F120XL"