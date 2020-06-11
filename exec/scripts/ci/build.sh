#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0
cd code/*/
make
cd ../../
echo 'Finished shell script' $0 '.'
#EOF