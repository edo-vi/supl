# Supl

## Description
C++ supervised learning library. Still work-in-progress.

Algorithms currently implemented: *K-Nearest Neighbors*.  

## How to run the example executable
```
mkdir build; cd $_; cmake ..; make; ./exampleKNN
```
This will build the library, the tests and the example program and will run this last one, that is, it will run the
K-NN algorithm on three different common datasets: *Iris*, *Wine*, and *Ecoli*, for the purpose of multiclass
classification, printing the testing errors.

## How to run the tests
Simply build the project with Cmake and then run in *build*
```
make test
```

## How to generate the documentation
After having built the project with cmake in *build* in the same folder just execute
```
make doc
```
This requires having the doxygen executable (called 'doxygen') in the *doc* folder and will generate the html
documentation in *doc/html*.