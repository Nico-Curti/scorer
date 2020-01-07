| **Authors**  | **Project** |  **Build Status** | **License** | **Code Quality** | **Coverage** |
|:------------:|:-----------:|:-----------------:|:-----------:|:----------------:|:------------:|
| [**N. Curti**](https://github.com/Nico-Curti) | **Scorer** | **Linux/MacOS** : [![travis](https://travis-ci.com/Nico-Curti/scorer.svg?branch=master)](https://travis-ci.com/Nico-Curti/scorer) <br/>  **Windows** : [![appveyor](https://ci.appveyor.com/api/projects/status/4whrmb6qsp3nefgp?svg=true)](https://ci.appveyor.com/project/Nico-Curti/scorer) | [![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Nico-Curti/Scorer/blob/master/LICENSE.md) | **Codacy** : [![Codacy](https://api.codacy.com/project/badge/Grade/569341573b4e438196ea012f906fd0d0)](https://www.codacy.com/manual/Nico-Curti/scorer?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Nico-Curti/scorer&amp;utm_campaign=Badge_Grade) <br/> **Codebeat** : [![CODEBEAT](https://codebeat.co/badges/7222a662-b62c-4481-9d40-136cd9ba17b6)](https://codebeat.co/projects/github-com-nico-curti-scorer-master) | [![codecov](https://codecov.io/gh/Nico-Curti/scorer/branch/master/graph/badge.svg)](https://codecov.io/gh/Nico-Curti/scorer) |

[![GitHub pull-requests](https://img.shields.io/github/issues-pr/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/pulls)
[![GitHub issues](https://img.shields.io/github/issues/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/issues)

[![GitHub stars](https://img.shields.io/github/stars/Nico-Curti/scorer.svg?label=Stars&style=social)](https://github.com/Nico-Curti/scorer/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/Nico-Curti/scorer.svg?label=Watch&style=social)](https://github.com/Nico-Curti/scorer/watchers)

# Machine Learning Scores

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

To build the project you can use the [Makefile](https://github.com/Nico-Curti/scorer/blob/master/Makefile) or the [CMake](https://github.com/Nico-Curti/scorer/blob/master/CMakeLists.txt) (recommended).

In the first case you can see the whole set of available rules just typing `make` or `make example` to build the [example](https://github.com/Nico-Curti/scorer/blob/master/example/example.cpp) script in c++ or `make pythonic` to build the Cython version of the code.

The builds scripts ([build.sh](https://github.com/Nico-Curti/scorer/blob/master/build.sh) and [build.ps1](https://github.com/Nico-Curti/scorer/blob/master/build.ps1)) allow an automatic build of the full library in Windows and Linux/MacOS systems using CMake.

```bash
git clone https://github.com/Nico-Curti/scorer.git
cd scorer
./build.sh
```

For a manual installation of the Python version you can also run the [setup](https://github.com/Nico-Curti/scorer/blob/master/setup.py) script as

```bash
python -m pip install -r requirements.txt
python setup.py build_ext --inplace
```

or for developers

```bash
python -m pip install -r requirements.txt
python setup.py develop --user
```

If you are working without *root* privileges we suggest to use the [`Shut`](https://github.com/Nico-Curti/shut) scripts to easily install all the required dependencies.

## Prerequisites

To build the c++ version of the code at least c++14 is required.
C++ supported compilers:

![gcc version](https://img.shields.io/badge/gcc-4.9.*%20|%205.*%20|%206.*%20|%207.*%20|%208.*%20|%209.*-yellow.svg)

![clang version](https://img.shields.io/badge/clang-3.*%20|4.*%20|5.*%20|%206.*%20|%207.*%20|-red.svg)

![msvc version](https://img.shields.io/badge/msvc-vs2017%20x86%20|%20vs2017%20x64-blue.svg)

Python version supported :

![Python version](https://img.shields.io/badge/python-2.7|3.3|3.4|3.5|3.6|3.7-blue.svg)

The OMP version of the code is automatically available if OMP is installed and in this way all the metric computations are performed in parallel according to the generated dependency graph.

The full list of prerequisites of Python version is listed in [requirements](https://github.com/Nico-Curti/scorer/blob/master/requirements.txt).

**Note**: if you are interested on the visualization of the dependency graph and some other utilities to manage the evaluated metrics you can find all the scripts in the [utils](https://github.com/Nico-Curti/scorer/tree/master/utils) folder.
In this case you need to install also the following Python packages:

```
networkx>=2.2
pandas>=0.23.3
matplotlib>=2.2.2
mpld3>=0.3
```

## Usage

You can use the libraries either inside your c++ project with a simple include of the [scorer.h](https://github.com/Nico-Curti/scorer/blob/master/include/scorer.h) header file or inside your Python application, where the scorer class is wrapped to give a simple dictionary in return.

If you use the c++ version *PAY ATTENTION* to the parallel environment (open the parallel region before the run of scores computation as shown in the following example code).

```c++
#include <array>
#include <scorer.h>

int main ()
{
  const int n_labels = 12;

  std :: array < int, n_labels > y_true = { {2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2} };
  std :: array < int, n_labels > y_pred = { {0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2} };

  scorer score;

#ifdef _OPENMP
#pragma omp parallel shared (score)
  {
#endif

    score.compute_score(y_true.data(), y_pred.data(), n_labels, n_labels);

#ifdef _OPENMP
  }
#endif

  score.print();

  return 0;
}
```

The same code can be rewritten in Python as

```python
#import numpy as np
from scorer import Scorer

y_true = [2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2] # np.array([2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2], dtype=np.int32)
y_pred = [0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2] # np.array([0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2], dtype=np.int32)

scorer = Scorer()
scorer.evaluate(y_true, y_pred)
print(scorer)
```

In the [utils](https://github.com/Nico-Curti/scorer/tree/master/utils) folder some utility scripts are reported.
The `make_script.py` allows to write the complete parallel version of the scorer class in c++.
In this way if you add a new operator to the library you can just run this code to update the scorer class parallelization strategies (computed in `dependency_graphs.py` script).

With `view_stats.py` you can see the complete graph of computed statistics with an HTML support for a more pleasant vision (e.g. [graph](https://github.com/Nico-Curti/scorer/blob/master/img/dependency_graph.gif))

**NOTE**: using `view_stats.py` you can find the error

```python
Object of type ndarray is not JSON serializable
```

I suggest to use the following command to overcome this `mpld3` issue:

```bash
python -m pip install --user "git+https://github.com/javadba/mpld3@display_fix"
```

A full list of informations about the score functions and their meaning can be found in the amazing [documentation](https://www.pycm.ir/doc/) of the original PyCM project.

## License

The `Scorer` package is licensed under the MIT "Expat" License. [![License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Nico-Curti/Scorer/blob/master/LICENSE.md)

## Contribution

Any contribution is more than welcome :heart:. Just fill an [issue](https://github.com/Nico-Curti/scorer/blob/master/ISSUE_TEMPLATE.md) or a [pull request](https://github.com/Nico-Curti/scorer/blob/master/PULL_REQUEST_TEMPLATE.md) and we will check ASAP!

See [here](https://github.com/Nico-Curti/scorer/blob/master/CONTRIBUTING.md) for further informations about how to contribute with this project.

## Authors

- **Nico Curti** [git](https://github.com/Nico-Curti), [unibo](https://www.unibo.it/sitoweb/nico.curti2)

See also the list of [contributors](https://github.com/Nico-Curti/Scorer/contributors) [![GitHub contributors](https://img.shields.io/github/contributors/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/graphs/contributors/) who participated to this project.

## Acknowledgments

Thanks goes to all contributors of this project:

| [<img src="https://avatars3.githubusercontent.com/u/23407684?s=400&v=4" width="100px;"/><br /><sub><b>Daniele Dall'Olio</b></sub>](https://github.com/DanieleDallOlio)
|:---:|

### Citation

If you have found `Scorer` helpful in your research, please consider citing the project

```tex
@misc{Scorer,
  author = {Nico Curti},
  title = {Scorer},
  year = {2019},
  publisher = {GitHub},
  howpublished = {\url{https://github.com/Nico-Curti/scorer}},
}
```
