# README

## About
Resolve the ps1-q2 problem of Stanford CS229 class (Andrew Ng) using c++.

- y = lwlr(X_train, y_train, x, tau)
- plot_lwlr(X_train, y_train, tau, resolution)
- In this release, the convergece of theta depends on the convergece of y.

## Dependences
- matplotlibcpp.h (https://github.com/lava/matplotlib-cpp)

## Usage
The training data is stored in the 'data/' folder and the executable file 'ps1-q2' is in the 'code/' folder. 
e.g. 

```bash
$ cd code
$ ./ps1-q2 ../data/x.dat ../data/y.dat
```

To recompile and relink the source files that are modified, just tap in:

```bash
$ cd code
$ ./cl.sh
```
