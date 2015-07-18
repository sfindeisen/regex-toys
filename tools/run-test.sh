#!/bin/sh

# echo "---- run-test.sh: $program ; IN: $testin OUT: $testresout ERR: $testreserr"
$program < $testin 1>$testout 2>$testerr
