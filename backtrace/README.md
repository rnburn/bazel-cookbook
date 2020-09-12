This example shows how you can set up a bazel project to give a full stack trace whenever your program
crashes.

Run
```
bazel run --config with_backtrace //:rocket
```
and you'll see the output
```
rocket: pestcontrol.cc:4: void remove_gator(): Assertion `false && "won't move"' failed.
signal 6 (Aborted), address is 0x147e from 0x7fef2cada3eb
#6 /proc/self/cwd/pestcontrol.cc:7
#7 /proc/self/cwd/pestcontrol.cc:9
#8 /proc/self/cwd/runway.cc:7
#9 /proc/self/cwd/runway.h:7
#11 /proc/self/cwd/main.cc:11
```
