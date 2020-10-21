#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re
import platform

try:
  from setuptools import setup
  from setuptools import Extension
  from setuptools import find_packages

  from setuptools import dist

  dist.Distribution().fetch_build_eggs(['Cython>=0.29'])

except ImportError:
  from distutils.core import setup
  from distutils.core import Extension
  from distutils.core import find_packages

from distutils import sysconfig
from Cython.Distutils import build_ext
from distutils.sysconfig import customize_compiler
from distutils.command.sdist import sdist as _sdist


def get_requires (requirements_filename):
  '''
  What packages are required for this module to be executed?

  Parameters
  ----------
    requirements_filename : str
      filename of requirements (e.g requirements.txt)

  Returns
  -------
    requirements : list
      list of required packages
  '''
  with open(requirements_filename, 'r') as fp:
    requirements = fp.read()

  return list(filter(lambda x: x != '', requirements.split()))


def read_description (readme_filename):
  '''
  Description package from filename

  Parameters
  ----------
    readme_filename : str
      filename with readme information (e.g README.md)

  Returns
  -------
    description : str
      str with description
  '''

  try:

    with open(readme_filename, 'r') as fp:
      description = '\n'
      description += fp.read()

    return description

  except IOError:
    return ''


def get_ext_filename_without_platform_suffix (filename):
    name, ext = os.path.splitext(filename)
    ext_suffix = sysconfig.get_config_var('EXT_SUFFIX')

    if ext_suffix == ext:
      return filename

    ext_suffix = ext_suffix.replace(ext, '')
    idx = name.find(ext_suffix)

    if idx == -1:
      return filename
    else:
      return name[:idx] + ext


class scorer_build_ext (build_ext):
  '''
  Custom build type
  '''

  def get_ext_filename (self, ext_name):

    if platform.system() == 'Windows':
    # The default EXT_SUFFIX of windows include the PEP 3149 tags of compiled modules
    # In this case I rewrite a custom version of the original distutils.command.build_ext.get_ext_filename function
      ext_path = ext_name.split('.')
      ext_suffix = '.pyd'
      filename = os.path.join(*ext_path) + ext_suffix
    else:
      filename = super().get_ext_filename(ext_name)

    return get_ext_filename_without_platform_suffix(filename)

  def build_extensions (self):

    customize_compiler(self.compiler)

    try:
      self.compiler.compiler_so.remove('-Wstrict-prototypes')

    except (AttributeError, ValueError):
      pass

    build_ext.build_extensions(self)


class sdist(_sdist):
  def run(self):
    self.run_command("build_ext")
    _sdist.run(self)

def read_version (CMakeLists):
  '''
  Read version from variables set in CMake file

  Parameters
  ----------
    CMakeLists : string
      Main CMakefile filename or path

  Returns
  -------
    version : tuple
      Version as (major, minor, revision) of strings
  '''
  major = re.compile(r'set\s+\(SCORER_MAJOR\s+(\d+)\)')
  minor = re.compile(r'set\s+\(SCORER_MINOR\s+(\d+)\)')
  revision = re.compile(r'set\s+\(SCORER_REVISION\s+(\d+)\)')

  with open(CMakeLists, 'r') as fp:
    cmake = fp.read()

  major_v = major.findall(cmake)[0]
  minor_v = minor.findall(cmake)[0]
  revision_v = revision.findall(cmake)[0]

  version = map(int, (major_v, minor_v, revision_v))

  return tuple(version)

def dump_version_file (here, version_filename):
  '''
  Dump the __version__.py file as python script

  Parameters
  ----------
    here : string
      Local path where the CMakeLists.txt file is stored

    version_filename: string
      Filename or path where to save the __version__.py filename
  '''

  VERSION = read_version(os.path.join(here, './CMakeLists.txt'))

  script = '''#!/usr/bin/env python
# -*- coding: utf-8 -*-

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']

__version__ = '{}.{}.{}'
'''.format(*VERSION)

  with open(version_filename, 'w') as fp:
    fp.write(script)


here = os.path.abspath(os.path.dirname(__file__)).replace('\\', '/')

# Package meta-data.
NAME = 'scorer'
DESCRIPTION = 'Multi-class scorer computation library'
URL = 'https://github.com/Nico-Curti/scorer'
EMAIL = 'nico.curti2@unibo.it'
AUTHOR = "Nico Curti, Daniele Dall'Olio"
REQUIRES_PYTHON = '>=2.7'
VERSION = None
KEYWORDS = 'machine-learning score-calculator confusion-matrix statistics parallel'
ENABLE_OMP = False

CPP_COMPILER = platform.python_compiler()
README_FILENAME = os.path.join(here, 'README.md')
REQUIREMENTS_FILENAME = os.path.join(here, 'requirements.txt')
VERSION_FILENAME = os.path.join(here, 'scorer', '__version__.py')

# Import the README and use it as the long-description.
# Note: this will only work if 'README.md' is present in your MANIFEST.in file!
try:
  LONG_DESCRIPTION = read_description(README_FILENAME)

except IOError:
  LONG_DESCRIPTION = DESCRIPTION

dump_version_file(here, VERSION_FILENAME)

# Load the package's __version__.py module as a dictionary.
about = {}
if not VERSION:
  with open(VERSION_FILENAME) as fp:
    exec(fp.read(), about)

else:
  about['__version__'] = VERSION

# parse version variables and add them to command line as definitions
Version = about['__version__'].split('.')

if 'GCC' in CPP_COMPILER or 'Clang' in CPP_COMPILER:
  cpp_compiler_args = ['-std=c++1z', '-g0']

  compile_args = [ '-Wno-unused-function', # disable unused-function warnings
                   '-Wno-narrowing', # disable narrowing conversion warnings
                    # enable common warnings flags
                   '-Wall',
                   '-Wextra',
                   '-Wno-unused-result',
                   '-Wno-unknown-pragmas',
                   '-Wfatal-errors',
                   '-Wpedantic',
                   '-march=native',
                   '-Ofast'
                 ]

  try:

    compiler, compiler_version = CPP_COMPILER.split()

  except ValueError:

    compiler, compiler_version = (CPP_COMPILER, '0')

  if ENABLE_OMP and compiler == 'GCC':
    linker_args = ['-fopenmp']

  else:
    linker_args = []

  if 'Clang' in CPP_COMPILER and 'clang' in os.environ['CXX']:
    cpp_compiler_args += ['-stdlib=libc++']

elif 'MSC' in CPP_COMPILER:
  cpp_compiler_args = ['/std:c++latest', '/Ox', '/Wall', '/W3']
  compile_args = []

  if ENABLE_OMP:
    linker_args = ['/openmp']
  else:
    linker_args = []

else:
  raise ValueError('Unknown c++ compiler arg')

define_args = [ '-DMAJOR={}'.format(Version[0]),
                '-DMINOR={}'.format(Version[1]),
                '-DREVISION={}'.format(Version[2]),
                #'-D__pythonic__'
              ]


whole_compiler_args = sum([cpp_compiler_args, compile_args, define_args], [])

cmdclass = {'build_ext': scorer_build_ext,
            'sdist': sdist}


setup(
  name                          = NAME,
  version                       = about['__version__'],
  description                   = DESCRIPTION,
  long_description              = LONG_DESCRIPTION,
  long_description_content_type = 'text/markdown',
  author                        = AUTHOR,
  author_email                  = EMAIL,
  maintainer                    = AUTHOR,
  maintainer_email              = EMAIL,
  python_requires               = REQUIRES_PYTHON,
  install_requires              = get_requires(REQUIREMENTS_FILENAME),
  url                           = URL,
  download_url                  = URL,
  keywords                      = KEYWORDS,
  setup_requires                = [# Setuptools 18.0 properly handles Cython extensions.
                                   'setuptools>=18.0',
                                   'cython'],
  packages                      = find_packages(include=['scorer', 'scorer.*'], exclude=('test', 'example')),
  include_package_data          = True,
  data_files                    = [('', ['CMakeLists.txt', 'README.md', 'LICENSE']),
                                   ('utils', ['./utils/dependency_graph.py', './utils/make_script.py', './utils/view_stats.py'])
                                  ],
  platforms                     = 'any',
  classifiers                   = [
                                    # Full list: https://pypi.python.org/pypi?%3Aaction=list_classifiers
                                    'Programming Language :: Python',
                                    'Programming Language :: Python :: 3',
                                    'Programming Language :: Python :: 3.6',
                                    'Programming Language :: Python :: Implementation :: CPython',
                                    'Programming Language :: Python :: Implementation :: PyPy'
                                  ],
  license                       = 'GNU Lesser General Public License v2 or later (LGPLv2+)',
  cmdclass                      = cmdclass,
  ext_modules                   = [
                                    Extension(name='.'.join(['scorer', 'lib', 'scorer']),
                                              sources=[
                                                       './scorer/source/scorer.pyx',
                                                       './src/scorer.cpp'
                                              ],
                                              include_dirs=[
                                                  './include',
                                                  './scorer/lib',
                                              ],
                                              library_dirs=[
                                                             './lib',
                                                             os.path.join('usr', 'lib'),
                                                             os.path.join('usr', 'local', 'lib'),
                                              ], # path to .a or .so file(s)
                                              extra_compile_args=whole_compiler_args,
                                              extra_link_args=linker_args,
                                              language='c++',
                                              ),
                                            ],
)
