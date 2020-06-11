#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0

cd tests/MTest/offTar/
M_RES=$(make)
cd ../../../
return $M_RES
echo 'Finished shell script' $0 '.'
#EOF