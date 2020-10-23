# Fake It Till You Make It

Simple C project that emulates the make progression terminal outputs
from build systems such as CMake and possibly others.

```
user@ubuntu-laptop:build$ make
Scanning dependencies of target mylib
[ 16%] Building C object myLib/CMakeFiles/mylib.dir/src/library.c.o
[ 33%] Linking C static library libmylib.a
[ 33%] Built target mylib
Scanning dependencies of target mylibTest
[ 50%] Building C object myLibTest/CMakeFiles/mylibTest.dir/main.c.o
[ 66%] Linking C executable mylibTest
[ 66%] Built target mylibTest
Scanning dependencies of target myApp
[ 83%] Building C object myApp/CMakeFiles/myApp.dir/main.c.o
[100%] Linking C executable myApp
[100%] Built target myApp
```


## TODO List

- Make the base program
- Add colour to the text
- Make argument parsing
    - To add options such as different build emulations i.e. emerge, ros build, etc.
    - To disable colours?
- Add dictionary that pulls random words and strings them together to make up fake names for source files.
- Random node tree generation that emulates a folder structure full of files. Each folder is recusively entered until the bottom is hit where in the build then starts on each source file


