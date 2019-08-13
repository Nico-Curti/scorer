| **Authors**  | **Project** |  **Build Status**             | **Latest Version** | **License** |
|:------------:|:-----------:|:-----------------------------:|:------------------:|:-----------:|
|   N. Curti   |    scorer   |  **Linux/MacOS** : [![travis](https://travis-ci.com/Nico-Curti/scorer.svg?branch=master)](https://travis-ci.com/Nico-Curti/scorer) <br/>  **Windows** : [![appveyor](https://ci.appveyor.com/api/projects/status/4whrmb6qsp3nefgp?svg=true)](https://ci.appveyor.com/project/Nico-Curti/scorer) | ![version](https://img.shields.io/badge/PyPI-v1.0.0-orange.svg?style=plastic) | [![license](https://img.shields.io/badge/license-GPL-blue.svg?style=plastic)](https://github.com/Nico-Curti/scorer/blob/master/LICENSE)

[![GitHub pull-requests](https://img.shields.io/github/issues-pr/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/pulls)
[![GitHub issues](https://img.shields.io/github/issues/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/issues)

[![GitHub stars](https://img.shields.io/github/stars/Nico-Curti/scorer.svg?label=Stars&style=social)](https://github.com/Nico-Curti/scorer/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/Nico-Curti/scorer.svg?label=Watch&style=social)](https://github.com/Nico-Curti/scorer/watchers)

# Machine Learning Scorer

<a href="https://github.com/Nico-Curti/scorer/blob/master/img/scorer.pdf">
<div class="image">
<img src="img/dependency_graph.gif" width="1010" height="392">
</div>
</a>

Optimization and extension of the [**PyCM**](https://github.com/sepandhaghighi/pycm) library with c++ support and network dependencies.

1. [Getting Started](#getting-started)
2. [Prerequisites](#prerequisites)
3. [Usage](#usage)
4. [License](#license)
5. [Contribution](#contribution)
6. [Authors](#authors)
7. [Acknowledgments](#acknowledgments)
8. [Citation](#citation)

## Getting Started

To build the project you can use the [Makefile](https://github.com/Nico-Curti/scorer/blob/master/Makefile) or the [CMake](https://github.com/Nico-Curti/scorer/blob/master/CMakeLists.txt).

In the first case you can see the whole set of available rules just typing `make` and `make example` to build the [example](https://github.com/Nico-Curti/scorer/blob/master/example/example.cpp) script in c++ or `make pythonic` to build the Cython version of the code.

The [builds](https://github.com/Nico-Curti/scorer/blob/master/build.sh) scripts (.sh and .ps1) allows to build the project with CMake support.

For a manual installation of pythonic version you can also run the [setup](https://github.com/Nico-Curti/scorer/blob/master/setup.py) script as `python setup.py build_ext --inplace`.

## Prerequisites

To build the c++ version of the code the standard c++17 support is required.

The OMP version of the code is automatically available if OMP is installed.

The full list of prerequisites of pythonic version is listed in [requirements](https://github.com/Nico-Curti/scorer/blob/master/requirements.txt).

## Usage

You can use the libraries either inside your c++ project with a simple include of the [scorer](https://github.com/Nico-Curti/scorer/blob/master/include/scorer.h) script or with python in which the scorer class is wrapped to give a simple dictionary in return.

If you use the c++ version *PAY ATTENTION* to the parallel environment (open the parallel region before the run of scorer computation as shown in the example code).

In [utils](https://github.com/Nico-Curti/scorer/tree/master/utils) some utilities scripts are reported.
The `make_script.py` allows to write the complete parallel version of the scorer class in c++ so that if you add a new operator to the library you can just run this code to update the scorer class parallelization strategies (computed in `dependency_graphs.py` script).

With `view_stats.py` script you can see the complete graph of computed statistics with an HTML support with a more pleasant vision (ex. [graph](https://github.com/Nico-Curti/scorer/blob/master/img/dependency_graph.gif))

## License

The `Scorer` package is licensed under the MIT "Expat" License. [![License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Nico-Curti/Scorer/blob/master/LICENSE.md)

## Contribution

Any contribution is more than welcome. Just fill an issue or a pull request and I will check ASAP!

If you want update the list of scorer functions please pay attention to the syntax of the operator and to the names of variables used to prevent the compatibility with python utilities scripts.

## Authors

* **Nico Curti** [git](https://github.com/Nico-Curti), [unibo](https://www.unibo.it/sitoweb/nico.curti2)

See also the list of [contributors](https://github.com/Nico-Curti/Scorer/contributors) [![GitHub contributors](https://img.shields.io/github/contributors/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/graphs/contributors/) who participated to this project.

## Acknowledgments

Thanks goes to all contributors of this project:

| [<img src="https://avatars3.githubusercontent.com/u/23407684?s=400&v=4" width="100px;"/><br /><sub><b>Daniele Dall'Olio</b></sub>](https://github.com/DanieleDallOlio)
|:---:|

and to Raffaele Pepe who help me with Blender instructions.

### Citation

If you have found `Scorer` helpful in your research, please consider citing the project

```tex
@misc{Scorer,
  author = {Nico Curti},
  title = {{S}corer},
  year = {2019},
  publisher = {GitHub},
  howpublished = {\url{https://github.com/Nico-Curti/scorer}},
}
```
