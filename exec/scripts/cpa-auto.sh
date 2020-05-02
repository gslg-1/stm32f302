#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo "Start shell script "$0
args="'$*'"
for module in "$args"
./exec/tools/cpachecker/scripts/cpa.sh -valueAnalysis-NoCegar-join -outputpath ./output/$module/CPAchecker -setprop analysis.checkCounterexamples=false -setprop solver.solver=SMTInterpol -setprop cpa.predicate.encodeBitvectorAs=INTEGER -setprop cpa.predicate.encodeFloatAs=RATIONAL ./output/prebuild/$module.p.c
#./exec/tools/cpachecker/scripts/cpa.sh -preprocess -valueAnalysis-NoCegar-join -outputpath ./output/CPAchecker -setprop analysis.checkCounterexamples=false -setprop solver.solver=SMTInterpol -setprop cpa.predicate.encodeBitvectorAs=INTEGER -setprop cpa.predicate.encodeFloatAs=RATIONAL ./exec/tools/cpachecker/doc/examples/example.c

echo 'Finished shell script' $0 '.'
#EOF