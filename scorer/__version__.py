#!/usr/bin/env python
# -*- coding: utf-8 -*-

__package__ = 'version'
__author__  = ['Nico Curti']

__email__ = ['nico.curit2@unibo.it']

from scorer.build import read_version

VERSION = read_version('./CMakeLists.txt')

__version__ = '.'.join(map(str, VERSION))
