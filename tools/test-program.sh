#!/bin/bash

MYDIR=`dirname $0`
timex=`which time`
program=$1

runTest () {
    testin=$1
    testout=`mktemp`
    testerr=`mktemp`

    export program testin testout testerr
    extime=$($timex -f 'User: %U Sys: %S Real: %E RSS max: %M kB K: %K kB D: %D kB' /bin/sh $MYDIR/run-test.sh 2>&1)

    if [ -f "$testout" ] ; then
        if [ -s "$testout" ] ; then
            cat $testout
            echo "$extime"
        else
            echo "Warning: STDOUT is empty: $testout" ;
        fi

        if [ -s "$testerr" ] ; then
            echo "Warning: STDERR present: $testerr" ;
        fi ;
    else
        echo "Error: no output file!" ;
    fi ;
};

################################
# The program
################################

for i in test/*.in ; do
    echo "==== Test case: $i";
    runTest $i
done
