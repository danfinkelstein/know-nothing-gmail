#!/bin/bash

prog=`which $1`
if [ ! -f $1.instr ]; 
then
    ~/workspace/lprof/instr/mutator $prog $prog.instr > $prog.instr.out
fi

ocmd=$@
p1i=$1.instr
cmd=${ocmd/$1/$1.instr}
$cmd
