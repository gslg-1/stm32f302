#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0

#if test -d "docs/code/review/feat_USBInterface"; then
#	echo "nice"
#else
#	echo "dmn"
#fi

#if test -f "docs/req/feat_USBInterface.md"; then
#	echo "nice"
#else
#	echo "dmn"
#fi

REV_LOC=docs/code/review/$1
REQ_MD=docs/req/$1.JSON

L_REV=$(ls "$REV_LOC")
L_MOD=$(jq '.modules[] | .id' "$REQ_MD")

echo "DB 0"
echo $L_REV
echo "DB 1"
echo $L_MOD
echo "DB 2"

for m in "${L_MOD}"
do
	if 
	echo "$m =  $LOOP_RES"
done
exit 1

echo 'Finished shell script' $0 '.'
#EOF