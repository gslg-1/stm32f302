#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0
# Global Variables
# Defult Result
RESULT=1
# Connected Device
DEVICE=$(ls /dev/ | grep ttyS)

function bildPro()
{
    cd tests/MTest/onTar/BasicFW
    make clean
    make
    cd ../../../../
}
function clearTTYBuff()
{
    # Loade known end
    ST-LINK_CLI -c -rst
    ST-LINK_CLI -c -run
    # read until end
    while [ ! -z "$RES_DONE" ] && read LINE_RES < /dev/$DEVICE
    do
        RES_DONE=$(echo $LINE_RES | grep <Done>)
        if [ ! -z "$RES_FAILED" ]
        then 
            echo "$De"
            return
        fi
    done
}

function inspectRes()
{
    local LOC_RES_VAL=$1
    # Get M-TEST Result
    ST-LINK_CLI -c -rst
    ST-LINK_CLI -c -run

    # Inspect Result
    while [ ! -z "$RES_DONE" ] && read LINE_RES < /dev/$DEVICE
    do
        echo $LINE_RES
        RES_FAILED=$(echo $LINE_RES | grep Failed )
        RES_DONE=$(echo $LINE_RES | grep <Done>)
        if [ ! -z "$RES_FAILED" ]
        then 
            echo "$RES_FAILED"
            eval $LOC_RES_VAL=1
            return
        fi
    done
}

# Build Target
bildPro
# Erase Target
ST-LINK_CLI -c -ME
# Load Image on Target
ST-LINK_CLI -c -P output/onTarMTest/BasicFW.hex
echo "DBG - Start clearing Buffer"
# Clear TTY Buffer
clearTTYBuff 
echo "DBG - Start inspection"
# Inspect Result
inspectRes RESULT
echo 'Finished shell script' $0 '.'

# Result 
echo $RESULT
#EOF