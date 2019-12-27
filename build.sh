#!/bin/bash

os=`uname`
echo "You are using" $os "system."

make -C src/

if [ "$os" == "Linux" ]; then
    make -C lua-vm/src linux
elif [ "$os" == "Darwin" ]; then
    make -C lua-vm/src macosx
else
    echo "Only support linux and macos now."
    exit
fi

cp lua-vm/src/luac tools/
cp src/zipluac tools/