Installation guide
==================

C++ supported compilers:

|gcc version|

|clang version|

|msvc version|

To build the c++ version of the code at least c++14 is required.
The OMP version of the code is automatically available if OMP is installed and in this way all the metric computations are performed in parallel according to the generated dependency graph.

The full list of prerequisites of Python version is the following:

- numpy>=1.16.0
- cython>=0.29

.. note::

	If you are interested on the visualization of the dependency graph and some other utilities to manage the evaluated metrics you can find all the scripts in the utils_ folder.
	In this case you need to install also the following Python packages:

	- networkx>=2.2
	- pandas>=0.23.3
	- matplotlib>=2.2.2
	- mpld3>=0.3


.. |gcc version| image:: https://img.shields.io/badge/gcc-4.9.*%20|%205.*%20|%206.*%20|%207.*%20|%208.*%20|%209.*-yellow.svg
.. |clang version| image:: https://img.shields.io/badge/clang-3.*%20|4.*%20|5.*%20|%206.*%20|%207.*%20|-red.svg
.. |msvc version| image:: https://img.shields.io/badge/msvc-vs2017%20x86%20|%20vs2017%20x64|%20vs2019%20x86%20|%20vs2019%20x64-blue.svg
.. _CMake: https://github.com/Nico-Curti/scorer/blob/master/CMakeLists.txt
.. _Makefile: https://github.com/Nico-Curti/scorer/blob/master/Makefile
.. _utils: https://github.com/Nico-Curti/scorer/tree/master/utils

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   CMake
   Python
