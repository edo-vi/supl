# Supl

## Description
C++ supervised learning library. Still work-in-progress.

Algorithms currently implemented: *K-Nearest Neighbors*.  

## How to run the example executable
```
mkdir build; cd $_; cmake ..; make;
```
This will build all targets, including the main library.

To run the example program, just invoke
```
make install
```
This will create the test executable in the bin folder; this is just a simple program this will apply the KNN algorithm on three different common datasets: 
*Iris*, *Wine*, and *Ecoli*, for the purpose of multiclass classification, printing the testing errors and chosen parameters.

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
This requires having doxygen installed.
