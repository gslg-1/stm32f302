#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo "Start shell script "$0

PBUILD_DIR="output/prebuild/$1.p.c"
BUILD_DIR="output/CPAchecker/bddAnalysis/$1"

mkdir -p "$BUILD_DIR"
./exec/tools/cpachecker/scripts/cpa.sh -bddAnalysis-bam-fullBlockAbstraction -outputpath "$BUILD_DIR" -setprop analysis.checkCounterexamples=false -setprop solver.solver=SMTInterpol -setprop cpa.predicate.encodeBitvectorAs=INTEGER -setprop cpa.predicate.encodeFloatAs=RATIONAL "$PBUILD_DIR"

echo 'Finished shell script' $0 '.'
#EOF