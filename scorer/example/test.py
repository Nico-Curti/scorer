#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
from __future__ import print_function

#import numpy as np
from scorer import Scorer

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']

if __name__ == '__main__':

  y_true = [2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2] # np.array([2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2], dtype=np.int32)
  y_pred = [0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2] # np.array([0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2], dtype=np.int32)

  scorer = Scorer()
  scorer.evaluate(y_true, y_pred)
  print(scorer)
