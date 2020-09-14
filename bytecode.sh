#!/bin/bash
if [ $# -ne 1 ]; then
  echo "You should input one lua file"
else
  if [ -f $1 ]; then
    rm -f lua.out*
    ./luac $1
    ./zipluac luac.out
    rm luac.out
  else
    echo "File" $1 "no exists"
  fi
fi
