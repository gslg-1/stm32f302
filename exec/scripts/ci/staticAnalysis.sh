#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0

args="'$*'"
rm -fr output/CPAchecker
mkdir output/CPAchecker
for module in "${@}"
do
    mkdir ./output/CPAchecker/$module
    ./exec/tools/cpachecker/scripts/cpa.sh -default -outputpath ./output/CPAchecker/$module -setprop analysis.checkCounterexamples=false -setprop solver.solver=SMTInterpol -setprop cpa.predicate.encodeBitvectorAs=INTEGER -setprop cpa.predicate.encodeFloatAs=RATIONAL ./output/prebuild/$module.p.c
done


echo 'Finished shell script' $0 '.'
#EOF