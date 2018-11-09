#!/usr/bin/python
import os
import sysconfig
import numpy as np
from Cython.Distutils import build_ext
from Cython.Build import cythonize

try:
  from setuptools import setup, Extension
except ImportError:
  from distutils.core import setup, Extension

from distutils.sysconfig import customize_compiler

class my_build_ext(build_ext):
  def build_extensions(self):
    customize_compiler(self.compiler)
    try:
      self.compiler.compiler_so.remove("-Wstrict-prototypes")
    except (AttributeError, ValueError):
      pass
    build_ext.build_extensions(self)


def get_requires():
  with open('requirements.txt', 'r') as f:
    requirements = f.read()
  return list(filter(lambda x: x != '', requirements.split()))

def read_description():
  try:
    with open('README.md') as r:
      description = '\n'
      description += r.read()
  except Exception:
    return ''

extra_compile_args = ['-std=c++17', '-g0', '-fopenmp', '-DPYTHONIC']

setup(
  name                = 'scorer',
  packages            = ['scorer'],
  version             = '1.2.1',
  description         = 'Multi-class scorer computation library',
  long_description    = read_description(),
  long_description_content_type = 'text/markdown',
  install_requires    = get_requires(),
  author              = 'Nico Curti',
  author_email        = 'nico.curti2@unibo.it',
  maintainer          = 'Nico Curti',
  maintainer_email    = 'nico.curti2@unibo.it',
  url                 = 'https://github.com/Nico-Curti/Scorer',
  download_url        = 'https://github.com/Nico-Curti/Scorer',
  keywords            = "machine_learning ML",
  platforms           = ['Mac OSX', 'POSIX',],
  classifiers         = [
      '...',
  ],
  python_requires     = '>=2.7',
  license             = 'GNU Lesser General Public License v2 or later (LGPLv2+)',
  cmdclass = {'build_ext': my_build_ext},
  ext_modules = [
      Extension(name='Pyscorer',#os.path.join(os.getcwd(), "pyc", "Pyscorer"),
                sources=[
                         os.path.join(os.getcwd(), 'pyc', 'Pyscorer.pyx')
                ],
                include_dirs=[
                    '.',
                    os.path.join(os.getcwd(), 'include'),
                ],
                library_dirs = [os.path.join(os.getcwd(), 'pyc')],  # path to .a or .so file(s)
                extra_compile_args = extra_compile_args,
                extra_link_args = ['-fopenmp'],
                language='c++',
                ),
              ],
)
