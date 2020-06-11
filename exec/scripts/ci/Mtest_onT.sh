#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0
# Build Target
cd tests/MTest/onTar/BasicFW
make clean
make
cd ../../../../

# Erase Target
ST-LINK_CLI -c -ME

# Load Image on Target
ST-LINK_CLI -c -P output/onTarMTest/BasicFW.hex

# Clear TTY Buffer

# Find Device
DEVICE=$(ls /dev/ | grep tty)

# Reset Device
ST-LINK_CLI -c -HRst

# Inspect Result
:readOn
    read LINE_RES < /dev/$DEVICE
    echo $LINE_RES | grep Failed && goto lFailed
    echo $LINE_RES | grep <Done> && goto lSucc
    goto readOn
:lFailed
    return 1
:lSucc
    return 0
echo 'Finished shell script' $0 '.'
#EOF