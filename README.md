# IBM Audio Interface Library for 32-bit DOS (AIL/32) v.1.05

A sandbox over AIL32. Build was ported for a modern environment with GNU Make
and OpenWatcom. For details, please read the `read.me.utf8.txt` file - an
official document for AIL32.

To build this you will need:
- OpenWatcom, suggested to install into `/opt/watcom`
- GNU Make is needed
- [jwasm](https://github.com/JWasm/JWasm) - a MASM-compatible assembler
- Then, to build this thing, run the `./build.sh` from a console on Linux
- Run `make deploy` to copy all public binaries into "out" directory (will be created)

-----------
## P.S.

How to build and install JWasm on Linux:
```
git clone https://github.com/JWasm/JWasm.git
cd JWasm
mkdir build
cd build
cmake ..
make -j 4
cp jwasm /usr/local/bin
```

