#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo "Start shell script "$0

#functions:
wrong_param () {
    echo "cpa-checker"
    echo "Expected Input:"
    echo "cpa-checker <Analysis Option> <Zu analysierendes File>"
    echo "Analysis Options:"
    echo "-v:\t Value Analysis"
    echo "-r:\t Reaching-Definitions Analysis"
    echo "-i:\t Interval Analysis"
    echo "-s:\t Sign Analysis"
    exit 1
}



# File exist test
#
#if test -f $1 ; then
#    echo "Super"
#
#else
#    wrong_param 1
#fi

echo 'Finished shell script' $0 '.'



#EOF