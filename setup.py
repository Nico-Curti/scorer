#!/usr/bin/python

import io
import os
import sys
from shutil import rmtree
import numpy as np
from Cython.Distutils import build_ext
from Cython.Build import cythonize

try:
  from setuptools import setup, Extension, find_packages
except ImportError:
  from distutils.core import setup, Extension, find_packages

from distutils.sysconfig import customize_compiler

# Package meta-data.
NAME = 'scorer'
DESCRIPTION = 'Multi-class scorer computation library.'
URL = 'https://github.com/Nico-Curti/scorer'
EMAIL = 'nico.curti2@unibo.it'
AUTHOR = 'Nico Curti'
REQUIRES_PYTHON = '>=2.7'
VERSION = None
KEYWORDS = "machine-learning score-calculator confusion-matrix statistics parallel"

def get_requires():
  with open('requirements.txt', 'r') as f:
    requirements = f.read()
  return list(filter(lambda x: x != '', requirements.split()))

class my_build_ext(build_ext):
  def build_extensions(self):
    customize_compiler(self.compiler)
    try:
      self.compiler.compiler_so.remove("-Wstrict-prototypes")
    except (AttributeError, ValueError):
      pass
    build_ext.build_extensions(self)

def read_description():
  try:
    with open('README.md') as r:
      description = '\n'
      description += r.read()
  except Exception:
    return ''

here = os.path.abspath(os.path.dirname(__file__))

# Import the README and use it as the long-description.
# Note: this will only work if 'README.md' is present in your MANIFEST.in file!
try:
  with io.open(os.path.join(here, 'README.md'), encoding='utf-8') as f:
    long_description = '\n' + f.read()
except FileNotFoundError:
  long_description = DESCRIPTION

# Load the package's __version__.py module as a dictionary.
about = {}
if not VERSION:
  with open(os.path.join(here, 'scorer', '__version__.py')) as f:
    exec(f.read(), about)
else:
  about['__version__'] = VERSION

extra_compile_args = ['-std=c++17', '-g0', '-fopenmp', '-DPYTHONIC']

setup(
  name                = NAME,
  version             = about['__version__'],
  description         = DESCRIPTION,
  long_description    = long_description,
  long_description_content_type = 'text/markdown',
  author              = AUTHOR,
  author_email        = EMAIL,
  maintainer          = AUTHOR,
  maintainer_email    = EMAIL,
  python_requires     = REQUIRES_PYTHON,
  install_requires    = get_requires(),
  url                 = URL,
  download_url        = URL,
  keywords            = KEYWORDS,
  packages            = find_packages(include=['scorer', 'scorer.*'], exclude=('test',)),
  platforms           = 'any',
  classifiers=[
    # Trove classifiers
    # Full list: https://pypi.python.org/pypi?%3Aaction=list_classifiers
    'License :: OSI Approved :: GPL License',
    'Programming Language :: Python',
    'Programming Language :: Python :: 3',
    'Programming Language :: Python :: 3.6',
    'Programming Language :: Python :: Implementation :: CPython',
    'Programming Language :: Python :: Implementation :: PyPy'
  ],
  license             = 'GNU Lesser General Public License v2 or later (LGPLv2+)',
  cmdclass = {'build_ext': my_build_ext},
  ext_modules = [
      Extension(name='Pyscorer',#os.path.join(os.getcwd(), "scorer", "Pyscorer"),
                sources=[
                         os.path.join(os.getcwd(), 'scorer', 'Pyscorer.pyx')
                ],
                include_dirs=[
                    '.',
                    os.path.join(os.getcwd(), 'scorer', 'include'),
                ],
                library_dirs = [os.path.join(os.getcwd(), 'scorer')],  # path to .a or .so file(s)
                extra_compile_args = extra_compile_args,
                extra_link_args = ['-fopenmp'],
                language='c++',
                ),
              ],
)
