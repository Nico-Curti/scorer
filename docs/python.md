# Python scorer

## Prerequisites

The only dependency of the scorer package are Cython, Numpy and Sklearn and you can easy install them with `pip install -r requirements.txt`. The file [requirements.txt](https://github.com/Nico-Curti/scorer/blob/master/requirements.txt) is available in the principal folder of the scorer project.


## Installation

First of all ensure that a right Python version is installed (Python >= 2.7 is required).
The [Anaconda/Miniconda](https://www.anaconda.com/) python version is recomended.

Download the project or the latest release:

```bash
git clone https://github.com/Nico-Curti/scorer
cd scorer
```

To install the prerequisites type:

```bash
pip install -r ./requirements.txt
```

In the `scorer` directory execute:

```bash
python setup.py install
```

or for installing in development mode:

```bash
python setup.py develop --user
```

The cython sources are built also with the CMakeLists during the Scorer library installation.
