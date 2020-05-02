#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo "Start shell script "$0

./exec/tools/cpachecker/scripts/cpa.sh $@ -setprop analysis.checkCounterexamples=false -setprop solver.solver=SMTInterpol -setprop cpa.predicate.encodeBitvectorAs=INTEGER -setprop cpa.predicate.encodeFloatAs=RATIONAL

echo 'Finished shell script' $0 '.'
#EOF