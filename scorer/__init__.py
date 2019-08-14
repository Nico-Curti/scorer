#!/usr/bin/env python
# -*- coding: utf-8 -*-

try:

  from .Scorer import Scorer

except ImportError:
  pass


__all__ = ['Scorer']

__package__ = 'Multi-statistical scorer'
__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']
