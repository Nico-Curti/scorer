| **Authors**  | **Project** |
|:------------:|:-----------:|
|   N. Curti   |    Scorer   |

# (Machine Learning Scorer)

Optimization and extension of the [**PyCM**](https://github.com/sepandhaghighi/pycm) library with c++ support and network dependencies.

1. [Getting Started](#getting-started)
2. [Prerequisites](#prerequisites)
3. [Usage](#usage)
4. [Contribution](#contribution)
5. [Authors](#authors)

## Getting Started

To build the project you can use the [Makefile](https://github.com/scorer/Makefile) or the [CMake](https://github.com/scorer/CMakeLists.txt).

In the first case you can see the whole set of available rules just typing `make` and `make example` to build the [example](https://github.com/scorer/example/example.cpp) script in c++ or `make pythonic` to build the Cython version of the code.

The [builds](https://github.com/scorer/build.sh) scripts (.sh and .ps1) allows to build the project with CMake support.

For a manual installation of pythonic version you can also run the [setup](https://github.com/scorer/setup.py) script as `python setup.py build_ext --inplace`.

## Prerequisites

To build the c++ version of the code the standard c++17 support is required.

The OMP version of the code is automatically available if OMP is installed.

The full list of prerequisites of pythonic version is listed in [requirements](https://github.com/scorer/requirements.txt).

## Usage

You can use the libraries either inside your c++ project with a simple include of the [scorer](https://github.com/scorer/include/scorer.h) script or with python in which the scorer class is wrapped to give a simple dictionary in return.

If you use the c++ version *PAY ATTENTION* to the parallel environment (open the parallel region before the run of scorer computation as shown in the example code).

In [utils](https://github.com/scorer/utils) some utilities scripts are reported.
The `build_scorer.py` allows to write the complete parallel version of the scorer class in c++ so that if you add a new operator to the library you can just run this code to update the scorer class parallelization strategies (computed in `dependency_graphs.py` script).

With `view_stats.py` script you can see the complete graph of computed statistics with an HTML support with a more pleasant vision (ex. [graph](https://github.com/scorer/img/dependency_graph.html))

## Contribution

Any contribution is more than welcome. Just fill an issue or a pull request and I will check ASAP!

If you want update the list of scorer functions please pay attention to the syntax of the operator and to the names of variables used to prevent the compatibility with python utilities scripts.

## Authors

* **Nico Curti** [git](https://github.com/Nico-Curti), [unibo](https://www.unibo.it/sitoweb/nico.curti2)

See also the list of [contributors](https://github.com/Nico-Curti/Scorer/contributors) [![GitHub contributors](https://img.shields.io/github/contributors/Naereen/StrapDown.js.svg)](https://GitHub.com/Nico-Curti/Scorer/graphs/contributors/) who participated in this project.

