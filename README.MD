# Describe
This template uses swig to build cpp class to python module,
build with cmake, and gtest & pytest to test.

Also demostrate making rpm and tarball.

## Dependencies
```
g++ >= 4.8.5
swig >= 2.0.10
cmake >= 3.10
gtest
pytest
python2 or python3
rpmbuild optional
```

## Build and test
```
mkdir cmake-build
cd cmake-build
cmake ..
make
make testcpp
make testpy2
```

## Project structrue
```
├── bin
│   └── hello            //start script
├── CMakeLists.txt       //cmake build file
├── hello.spec.in        //rpmbuild input file
├── install.sh           //install script
├── make-rpm.sh          //rpmbuild
├── make-tarball.sh      //make a tarball
├── python               //python module
│   ├── CMakeLists.txt
│   ├── hello.py
│   └── hellotool.i
├── src                  //hello src files
│   ├── hello.cpp
│   ├── hello.h
│   └── utils.h
└── test                 //hello test files
    ├── CMakeLists.txt
    ├── test_hello.cpp
    └── test_hello.py
```

## Tarball structure
```
├── bin
│   ├── hello
│   └── ho -> hello
├── hello.py
├── install.sh
└── py_package
    ├── hellotool.py
    └── _hellotool.so
```

