welcome to breadbutter,a openbsd and sbase inspired alternative to gnu coreutils, toybox and busybox

status:

brb is complete as a minimal openbsd and sbase inspired userland.
further changes may happen but the core design is finished.

here is how to get it up and running. it is pretty simple and should only take a few seconds since i optimized the hell and heck out of the compiler settings.

building brb:

first, make sure you are in the root of the repo. then run:

make

that is it. the makefile will grab everything in usr/, crunch it down, and vomit a tiny binary called breadbutter inside a new bin/ folder for your pleasure and not mine. it also automatically creates all 58 symlinks for you so you don't have to do it by hand.

how to use it:
after the build finishes, you can test any command by pointing to the bin/ folder:

./bin/ls
./bin/date
./bin/cz -d somefile.cz

if you want to use these commands everywhere like a real brb/linux distro, just add that folder to your path:

export PATH="$PWD/bin:$PATH"

cleaning up:
if you want to start fresh or wipe the builds, just run:

make clean
