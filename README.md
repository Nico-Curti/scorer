| **Authors**  | **Project** |  **Documentation** | **Build Status** | **License** | **Code Quality** | **Coverage** |
|:------------:|:-----------:|:------------------:|:----------------:|:-----------:|:----------------:|:------------:|
| [**N. Curti**](https://github.com/Nico-Curti) <br/> [**D. Dall'Olio**](https://github.com/DanieleDallOlio) | **Scorer** | **Docs CI:** [![Scorer Docs CI](https://github.com/Nico-Curti/scorer/actions/workflows/docs.yml/badge.svg)](https://github.com/Nico-Curti/scorer/actions/workflows/docs.yml) <br/> [![docs](https://readthedocs.org/projects/scorer/badge/?version=latest)](https://scorer.readthedocs.io/en/latest/?badge=latest) | **Linux:** [![Linux scorer CI](https://github.com/Nico-Curti/scorer/actions/workflows/linux.yml/badge.svg)](https://github.com/Nico-Curti/scorer/actions/workflows/linux.yml) <br/> **Windows:** [![Windows scorer CI](https://github.com/Nico-Curti/scorer/actions/workflows/windows.yml/badge.svg)](https://github.com/Nico-Curti/scorer/actions/workflows/windows.yml)  <br/> **MacOS:** [![MacOS scorer CI](https://github.com/Nico-Curti/scorer/actions/workflows/macos.yml/badge.svg)](https://github.com/Nico-Curti/scorer/actions/workflows/macos.yml) <br/> **Python:** [![Python scorer CI](https://github.com/Nico-Curti/scorer/actions/workflows/python.yml/badge.svg)](https://github.com/Nico-Curti/scorer/actions/workflows/python.yml) | [![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Nico-Curti/Scorer/blob/master/LICENSE.md) | **Codacy** : [![Codacy](https://api.codacy.com/project/badge/Grade/569341573b4e438196ea012f906fd0d0)](https://www.codacy.com/manual/Nico-Curti/scorer?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Nico-Curti/scorer&amp;utm_campaign=Badge_Grade) <br/> **Codebeat** : [![CODEBEAT](https://codebeat.co/badges/7222a662-b62c-4481-9d40-136cd9ba17b6)](https://codebeat.co/projects/github-com-nico-curti-scorer-master) | [![codecov](https://codecov.io/gh/Nico-Curti/scorer/branch/master/graph/badge.svg)](https://codecov.io/gh/Nico-Curti/scorer) |

**Travis/Appveyor:** [![travis](https://travis-ci.com/Nico-Curti/scorer.svg?branch=master)](https://travis-ci.com/Nico-Curti/scorer)
[![appveyor](https://ci.appveyor.com/api/projects/status/4whrmb6qsp3nefgp?svg=true)](https://ci.appveyor.com/project/Nico-Curti/scorer)

[![GitHub pull-requests](https://img.shields.io/github/issues-pr/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/pulls)
[![GitHub issues](https://img.shields.io/github/issues/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/issues)
[![Download counter](http://pepy.tech/badge/scorer)](http://pepy.tech/count/scorer)

[![GitHub stars](https://img.shields.io/github/stars/Nico-Curti/scorer.svg?label=Stars&style=social)](https://github.com/Nico-Curti/scorer/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/Nico-Curti/scorer.svg?label=Watch&style=social)](https://github.com/Nico-Curti/scorer/watchers)

# Machine Learning Scores

<a href="https://github.com/Nico-Curti/scorer/blob/master/img/scorer.pdf">
  <div class="image">
    <img src="https://github.com/Nico-Curti/scorer/blob/master/img/dependency_graph.gif" width="1010" height="392">
  </div>
</a>

We propose a `C++` version of the [**PyCM**](https://github.com/sepandhaghighi/pycm) Python package.
Our implementation optimizes and extends the original library including multi-threading support and an easy-to-use interface to the main algorithm.
To further improve the usage of our code, we propose also a `Python` wrap of the library with a full compatibility with the [`scikit-learn`](https://github.com/scikit-learn/scikit-learn) package.

* [Overview](#overview)
* [Getting Started](#getting-started)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
* [Usage](#usage)
* [Testing](#testing)
* [Table of contents](#table-of-contents)
* [Contribution](#contribution)
* [References](#references)
* [FAQ](#faq)
* [Authors](#authors)
* [License](#license)
* [Acknowledgments](#acknowledgments)
* [Citation](#citation)

## Overview

A full list of informations about the score functions and their meaning can be found in the amazing [documentation](https://www.pycm.ir/doc/) of the original PyCM project.

## Getting Started

To build the project you can use the [Makefile](https://github.com/Nico-Curti/scorer/blob/master/Makefile) or the [CMake](https://github.com/Nico-Curti/scorer/blob/master/CMakeLists.txt) (recommended).

In the first case you can see the whole set of available rules just typing `make` or `make example` to build the [example](https://github.com/Nico-Curti/scorer/blob/master/example/example.cpp) script in c++ or `make pythonic` to build the Cython version of the code.

The builds scripts ([build.sh](https://github.com/Nico-Curti/scorer/blob/master/build.sh) and [build.ps1](https://github.com/Nico-Curti/scorer/blob/master/build.ps1)) allow an automatic build of the full library in Windows and Linux/MacOS systems using CMake.

```bash
git clone https://github.com/Nico-Curti/scorer.git
cd scorer
./build.sh Release
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

> :warning: The setup file requires the `Cython` package, thus make sure to pre-install them!
> We are working on some workarounds to solve this issue.

> :warning: The current installation via pip has no requirements about the version of `setuptools` package.
> If the already installed version of `setuptools` is `>= 50.*` you can find some troubles during the installation of our package (ref. [issue](https://github.com/Nico-Curti/rFBP/issues/5)).
> We suggest to temporary downgrade the `setuptools` version to `49.3.0` to workaround this `setuptools` issue.

## Prerequisites

To build the c++ version of the code at least c++14 is required.
C++ supported compilers:

![gcc version](https://img.shields.io/badge/gcc-4.9.*|5.*|6.*|7.*|8.*|9.*|10.*-yellow.svg)

![clang version](https://img.shields.io/badge/clang-3.*|4.*|5.*|6.*|7.*|8.*|9.*|10.*-red.svg)

![msvc version](https://img.shields.io/badge/msvc-vs2017%20x86%20|%20vs2017%20x64|%20vs2019%20x86%20|%20vs2019%20x64-blue.svg)

Python version supported :

![Python version](https://img.shields.io/badge/python-2.7|3.3|3.4|3.5|3.6|3.7|3.8|3.9-blue.svg)

The OMP version of the code is automatically available if OMP is installed and in this way all the metric computations are performed in parallel according to the generated dependency graph.

The full list of prerequisites of Python version is listed in [requirements](https://github.com/Nico-Curti/scorer/blob/master/requirements.txt).

**Note**: if you are interested on the visualization of the dependency graph and some other utilities to manage the evaluated metrics you can find all the scripts in the [utils](https://github.com/Nico-Curti/scorer/tree/master/utils) folder.
In this case you need to install also the following Python packages:

- pandas>=0.23.3
- matplotlib>=2.2.2
- mpld3>=0.3

> :warning: For both the Python and C++ installation of the library is required Python with the support of [`networkx`](https://networkx.github.io/) package.
> Thus, please configure your Python such as the CMake `find_package` function can find it and pay attention to install the `networkx` package for the auto-generation of the scorer object!

## Installation

A complete list of instructions "for beginners" is also provided for both [c++](https://scorer.readthedocs.io/en/latest/CMake.html) and [python](https://scorer.readthedocs.io/en/latest/Python.html) versions.

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

The same code can be rewritten in Python (also with different labels dtype) as

```python
#import numpy as np
from scorer import Scorer

y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
# y_true = np.array([2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2], dtype=np.int32)
y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']
# y_pred = np.array([0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2], dtype=np.int32)

scorer = Scorer()
scorer.evaluate(y_true, y_pred)
print(scorer)
```

The output is the same in both the executions and it should be something like this

```
$ python ./scorer/example/main.py
Classes: 0, 1, 2
Confusion Matrix:
 3.0 0.0 0.0
 0.0 1.0 2.0
 2.0 1.0 3.0

Class Statistics:

TP(True positive/hit)                                                                           3.000                1.000                3.000
FN(False negative/miss/type 2 error)                                                            0.000                2.000                3.000
FP(False positive/type 1 error/false alarm)                                                     2.000                1.000                2.000
TN(True negative/correct rejection)                                                             7.000                8.000                4.000
POP(Population)                                                                                12.000               12.000               12.000
P(Condition positive or support)                                                                3.000                3.000                6.000
N(Condition negative)                                                                           9.000                9.000                6.000
TOP(Test outcome positive)                                                                      5.000                2.000                5.000
TON(Test outcome negative)                                                                      7.000               10.000                7.000
TPR(Sensitivity / recall / hit rate / true positive rate)                                       1.000                0.333                0.500
TNR(Specificity or true negative rate)                                                          0.778                0.889                0.667
PPV(Precision or positive predictive value)                                                     0.600                0.500                0.600
NPV(Negative predictive value)                                                                  1.000                0.800                0.571
FNR(Miss rate or false negative rate)                                                           0.000                0.667                0.500
FPR(Fall-out or false positive rate)                                                            0.222                0.111                0.333
FDR(False discovery rate)                                                                       0.400                0.500                0.400
FOR(False omission rate)                                                                        0.000                0.200                0.429
ACC(Accuracy)                                                                                   0.833                0.750                0.583
F1(F1 score - harmonic mean of precision and sensitivity)                                       0.750                0.400                0.545
F0.5(F0.5 score)                                                                                0.652                0.455                0.577
F2(F2 score)                                                                                    0.882                0.357                0.517
MCC(Matthews correlation coefficient)                                                           0.683                0.258                0.169
BM(Informedness or bookmaker informedness)                                                      0.778                0.222                0.167
MK(Markedness)                                                                                  0.600                0.300                0.171
PLR(Positive likelihood ratio)                                                                  4.500                3.000                1.500
NLR(Negative likelihood ratio)                                                                  0.000                0.750                0.750
DOR(Diagnostic odds ratio)                                                                        inf                4.000                2.000
PRE(Prevalence)                                                                                 0.250                0.250                0.500
G(G-measure geometric mean of precision and sensitivity)                                        0.775                0.408                0.548
RACC(Random accuracy)                                                                           0.104                0.042                0.208
ERR(Error rate)                                                                                 0.167                0.250                0.417
RACCU(Random accuracy unbiased)                                                                 0.111                0.043                0.210
J(Jaccard index)                                                                                0.600                0.250                0.375
IS(Information score)                                                                           1.263                1.000                0.263
CEN(Confusion entropy)                                                                          0.250                0.497                0.604
MCEN(Modified confusion entropy)                                                                0.264                0.500                0.688
AUC(Area Under the ROC curve)                                                                   0.889                0.611                0.583
dInd(Distance index)                                                                            0.222                0.676                0.601
sInd(Similarity index)                                                                          0.843                0.522                0.575
DP(Discriminant power)                                                                            inf                0.332                0.166
Y(Youden index)                                                                                 0.778                0.222                0.167
PLRI(Positive likelihood ratio interpretation)                                                   Poor                 Poor                 Poor
NLRI(Negative likelihood ratio interpretation)                                                   Good           Negligible           Negligible
DPI(Discriminant power interpretation)                                                           None                 Poor                 Poor
AUCI(AUC value interpretation)                                                              Very Good                 Fair                 Poor
GI(Gini index)                                                                                  0.778                0.222                0.167
LS(Lift score)                                                                                  2.400                2.000                1.200
AM(Difference between automatic and manual classification)                                      2.000               -1.000               -1.000
OP(Optimized precision)                                                                         0.708                0.295                0.440
IBA(Index of balanced accuracy)                                                                 0.951                0.132                0.278
GM(G-mean geometric mean of specificity and sensitivity)                                        0.882                0.544                0.577
Q(Yule Q - coefficient of colligation)                                                            nan                0.600                0.333
AGM(Adjusted geometric mean)                                                                    0.837                0.692                0.607
MCCI(Matthews correlation coefficient interpretation)                                        Moderate           Negligible           Negligible
AGF(Adjusted F-score)                                                                           0.914                0.540                0.552
OC(Overlap coefficient)                                                                         1.000                0.500                0.600
OOC(Otsuka-Ochiai coefficient)                                                                  0.775                0.408                0.548
AUPR(Area under the PR curve)                                                                   0.800                0.417                0.550
BCD(Bray-Curtis dissimilarity)                                                                  0.083                0.042                0.042
ICSI(Individual classification success index)                                                   0.600               -0.167                0.100

Overall Statistics:

Overall ACC                                                                      0.583
Overall RACCU                                                                    0.365
Overall RACC                                                                     0.354
Kappa                                                                            0.355
Scott PI                                                                         0.344
Gwet AC1                                                                         0.389
Bennett S                                                                        0.375
Kappa Standard Error                                                             0.220
Kappa Unbiased                                                                   0.344
Kappa No Prevalence                                                              0.167
Kappa 95% CI                                                                     (0.7867531180381775, -0.0770757719874382)
Standard Error                                                                   0.142
95% CI                                                                           (0.8622781038284302, 0.30438855290412903)
Chi-Squared                                                                      6.600
Phi-Squared                                                                      0.550
Cramer V                                                                         0.524
Response Entropy                                                                 1.483
Reference Entropy                                                                1.500
Cross Entropy                                                                    1.594
Joint Entropy                                                                    2.459
Conditional Entropy                                                              0.959
Mutual Information                                                               0.524
KL Divergence                                                                    0.094
Lambda B                                                                         0.429
Lambda A                                                                         0.167
Chi-Squared DF                                                                   4.000
Overall J                                                                        (1.225000023841858, 0.40833333134651184)
Hamming loss                                                                     0.417
Zero-one Loss                                                                    5.000
NIR                                                                              0.500
P-value                                                                          0.387
Overall CEN                                                                      0.464
Overall MCEN                                                                     0.519
Overall MCC                                                                      0.367
RR                                                                               4.000
CBA                                                                              0.478
AUNU                                                                             0.694
AUNP                                                                             0.667
RCI                                                                              0.349
Pearson C                                                                        0.596
F1 Micro                                                                         0.583
PPV Micro                                                                        0.583
TPR Micro                                                                        0.583
SOA1(Landis & Koch)                                                              Fair
SOA2(Fleiss)                                                                     Poor
SOA3(Altman)                                                                     Fair
SOA4(Cicchetti)                                                                  Poor
SOA5(Cramer)                                                                     Relatively Strong
SOA6(Matthews)                                                                   Weak
ACC Macro                                                                        0.722
F1 Macro                                                                         0.565
TPR Macro                                                                        0.611
PPV Macro                                                                        0.567
CSI                                                                              0.178
```

If you are working with non-integer labels the Scorer object provides a usefull `_label2numbers` (`encode` in C++) function.
Its usage is mandatory in `C++` since the function signature requires **only** integer (int32) values, while the `Python` version automatically encode/decode the labels according to requirements.

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

## Testing

The Python version of the package is tested using [`pytest`](https://docs.pytest.org/en/latest/).
To install the package in development mode you need to add also this requirement:

* pytest == 3.0.7
* hypothesis == 4.13.0

The full list of python test scripts can be found [here](https://github.com/Nico-Curti/scorer/blob/master/testing).

## Table of contents

Description of the folders related to the `C++` version.

| **Directory**  |  **Description** |
|:--------------:|:-----------------|
| [example](https://github.com/Nico-Curti/scorer/blob/master/example) | List of example usages for the C++ version of the code.                      |
| [include](https://github.com/Nico-Curti/scorer/blob/master/include) | Definition of the C++ function and objects used in the `scorer` library      |
| [src](https://github.com/Nico-Curti/scorer/blob/master/src)         | Implementation of the C++ functions and objects used in the `scorer` library |

Description of the folders related to the `Python` version (base directory `scorer`).

| **Directory**  |  **Description** |
|:--------------:|:-----------------|
| [example](https://github.com/Nico-Curti/scorer/blob/master/scorer/example) | `Python` version of the `C++` examples. |
| [lib](https://github.com/Nico-Curti/scorer/blob/master/scorer/lib)         | List of `Cython` definition files       |
| [source](https://github.com/Nico-Curti/scorer/blob/master/scorer/source)   | List of `Cython` implementation objects |
| [scorer](https://github.com/Nico-Curti/scorer/blob/master/scorer/scorer)   | List of `Python` wraps                  |

## Contribution

Any contribution is more than welcome :heart:. Just fill an [issue](https://github.com/Nico-Curti/scorer/blob/master/.github/ISSUE_TEMPLATE/ISSUE_TEMPLATE.md) or a [pull request](https://github.com/Nico-Curti/scorer/blob/master/.github/PULL_REQUEST_TEMPLATE/PULL_REQUEST_TEMPLATE.md) and we will check ASAP!

See [here](https://github.com/Nico-Curti/scorer/blob/master/.github/CONTRIBUTING.md) for further informations about how to contribute with this project.

## References

<blockquote>1- Haghighi, S., Jasemi, M., Hessabi, S. and Zolanvari, A. (2018). PyCM: Multiclass confusion matrix library in Python. Journal of Open Source Software, 3(25), p.729. </blockquote>

## FAQ

* **How can I properly set the C++ compiler for the Python installation?**

If you are working on a Ubuntu machine pay attention to properly set the environment variables related to the `C++` compiler.
First of all take care to put the compiler executable into your environmental path:

```bash
ls -ltA /usr/bin | grep g++
```

Then you can simply use the command to properly set the right aliases/variables

```bash
export CXX=/usr/bin/g++
export CC=/usr/bin/gcc
```

but I suggest you to put those lines into your `.bashrc` file (one for all):

```bash
echo "export CC=/usr/bin/gcc" >> ~/.bashrc
echo "export CXX=/usr/bin/g++" >> ~/.bashrc
```

I suggest you to not use the default `Python` compiler (aka `x86_64-linux-gnu-g++`) since it can suffer of many issues during the compilation if it is not manually customized.

**Note:** If you are working under Windows OS a complete guide on how to properly configure your MSVC compiler can be found [here](https://github.com/physycom/sysconfig).

## Authors

* <img src="https://avatars0.githubusercontent.com/u/24650975?s=400&v=4" width="25px"> **Nico Curti** [git](https://github.com/Nico-Curti), [unibo](https://www.unibo.it/sitoweb/nico.curti2)
* <img src="https://avatars3.githubusercontent.com/u/23407684?s=400&v=4" width="25px"> **Daniele Dall'Olio** [git](https://github.com/DanieleDallOlio), [unibo](https://www.unibo.it/sitoweb/daniele.dallolio)

See also the list of [contributors](https://github.com/Nico-Curti/Scorer/contributors) [![GitHub contributors](https://img.shields.io/github/contributors/Nico-Curti/scorer.svg?style=plastic)](https://github.com/Nico-Curti/scorer/graphs/contributors/) who participated to this project.

## License

The `Scorer` package is licensed under the MIT "Expat" License. [![License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Nico-Curti/Scorer/blob/master/LICENSE)

## Acknowledgments

Thanks goes to all contributors of this project.

### Citation

If you have found `Scorer` helpful in your research, please consider citing the project

```BibTeX
@misc{Scorer,
  author = {Nico Curti \& Daniele Dall'Olio},
  title = {Scorer},
  year = {2019},
  publisher = {GitHub},
  howpublished = {\url{https://github.com/Nico-Curti/scorer}},
}
```
