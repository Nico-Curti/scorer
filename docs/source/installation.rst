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
- networkx>=2.2
- scikit-learn>=0.24.0

.. note::

	If you are interested on the visualization of the dependency graph and some other utilities to manage the evaluated metrics you can find all the scripts in the utils_ folder.
	In this case you need to install also the following Python packages:

	- pandas>=0.23.3
	- matplotlib>=2.2.2
	- mpld3>=0.3

.. warning::

	For both the Python and C++ installation of the library is required Python with the support of `networkx`_ package.
	Thus, please configure your Python such as the CMake `find_package` function can find it and pay attention to install the `networkx` package for the auto-generation of the scorer object!

.. warning::

  The `Python` installation can be performed with or without the `C++` installation.
  The `Python` installation is always executed using [`setup.py`](https://github.com/Nico-Curti/scorer/blob/master/setup.py) script.
  Thus, if you have already build the C++ library with the CMake script you have to run the setup.py script to obtain the Python package!

FAQ
---

* **How can I properly set the C++ compiler for the Python installation?**

If you are working on a Ubuntu machine pay attention to properly set the environment variables related to the `C++` compiler.
First of all take care to put the compiler executable into your environmental path:

.. code-block:: bash

  ls -ltA /usr/bin | grep g++

Then you can simply use the command to properly set the right aliases/variables

.. code-block:: bash

  export CXX=/usr/bin/g++
  export CC=/usr/bin/gcc

but I suggest you to put those lines into your `.bashrc` file (one for all):

.. code-block:: bash

  echo "export CC=/usr/bin/gcc" >> ~/.bashrc
  echo "export CXX=/usr/bin/g++" >> ~/.bashrc

I suggest you to not use the default `Python` compiler (aka `x86_64-linux-gnu-g++`) since it can suffer of many issues during the compilation if it is not manually customized.

**Note:** If you are working under Windows OS a complete guide on how to properly configure your MSVC compiler can be found here_.

* **I installed the `scorer` Python package following the instructions but I have an `ImportError` when I try to import the package as in the examples**

This error is due a missing environment variable (which is not automatically set by the installation script).
All the `C++` libraries are searched into the OS directory tree starting from the information/paths hinted by the `LD_LIBRARY_PATH` environment variable.
When you install the `scorer` library the produced `.so`, `.dll`, `.dylib` files are saved into the `lib` directory created into the project root directory.
After the installation you must add this directory into the searching path.
You can add this information editing the configuration file of your `Unix`-like system, i.e

.. code-block:: bash

  echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/scorer/project/directory/lib/" >> ~/.bashrc
  echo "export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:/path/to/scorer/project/directory/lib/" >> ~/.bashrc

or adding the `LD_LIBRARY_PATH` to your set of environment variables (especially for `Windows` users).

.. |gcc version| image:: https://img.shields.io/badge/gcc-4.9.*|5.*|6.*|7.*|8.*|9.*|10.*-yellow.svg
.. |clang version| image:: https://img.shields.io/badge/clang-3.*|4.*|5.*|6.*|7.*|8.*|9.*|10.*-red.svg
.. |msvc version| image:: https://img.shields.io/badge/msvc-vs2017%20x86%20|%20vs2017%20x64|%20vs2019%20x86%20|%20vs2019%20x64-blue.svg
.. _CMake: https://github.com/Nico-Curti/scorer/blob/master/CMakeLists.txt
.. _Makefile: https://github.com/Nico-Curti/scorer/blob/master/Makefile
.. _utils: https://github.com/Nico-Curti/scorer/tree/master/utils
.. _`networkx`: https://networkx.github.io/
.. _here: https://github.com/physycom/sysconfig

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   CMake
   Python
