#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']


def read_version (CMakeLists):
  '''
  Read version from variables set in CMake file

  Parameters
  ----------
  CMakeLists : CMake file path

  Returns
  -------
  version : tuple
    Version as (major, minor, revision)
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

try:

  LOCAL = os.path.join(os.path.dirname(__file__), '..')

except NameError:

  LOCAL = ''

VERSION = read_version(os.path.join(LOCAL, './CMakeLists.txt'))

__version__ = '.'.join(map(str, VERSION))
