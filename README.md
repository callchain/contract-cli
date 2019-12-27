# Contract Tools

User use this tool to compile lua contract to lua bytecode and compress bytecode by snappy. The compress lua bytecode is convenient for network transmission and blockchain storage. This tool only support Linux system and MacOS system now.

## Dependency

### snappy
snappy - (https://github.com/google/snappy)

In Centos system
`sh
yum install snappy
`
In Ubuntu system
`sh
apt install libsnappy-dev
`
In MacOS system
`sh
brew instlal libsnappy-dev
`

## Build

1. Pull lua virtual machine code

`sh
git submodule update --init --recursive
`

2. Build luac and zipluac command, collect these commands to tools directory. Then tools directory is build output

`sh
./build.sh
`

## Usage

In tools directory

sh
`
./compile.sh [your contract lua file name]
`

The out.hex file is output file.
