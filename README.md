# Lua Contract Tools

## Overview

User use this contract tool to convert lua source contract file to lua bytecode which is compressed by snappy. Compressed bytecode is convenient fo network transmission and system storage.

Now this tool only support Linux system and MacOS system.


## Dependency

1. snappy - (https://github.com/google/snappy)

2. readline


In Centos system

```bash
yum install snappy
yum install libreadline-dev
```

In Ubuntu system

```bash
apt install libsnappy-dev
apt install libreadline-dev
```

In MacOS system

```bash
brew install libsnappy-dev
brew install libreadline-dev
```

## Build

1. Pull lua virtual machine code

```
git submodule update --init --recursive
```

2. Build luac and zipluac command, collect these commands to tools directory. Then tools directory is build output

```
./build.sh
```

## Usage

In tools directory

```
./bytecode.sh [your contract lua file name]
```

The luac.out.hex file is output file.

Compile example

```
./bytecode.sh ../examples/hello.lua
```

## LICENSE

See LICENSE file in this project.

