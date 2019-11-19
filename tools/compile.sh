#!/bin/bash
if [ $# -ne 1 ]; then
  echo "You should input 1 parameter"
else
  if [ -f $1 ]; then
    rm -f lua.out*
    ./luac $1
    ./zipluac luac.out
  else
    echo "File" $1 "no exists"
  fi
fi
