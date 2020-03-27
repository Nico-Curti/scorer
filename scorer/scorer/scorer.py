#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
from __future__ import print_function

from scorer.lib.scorer import _scorer

import numpy as np
import warnings

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']


class Scorer (object):

  def __init__ (self):
    '''
    Multi-class score computation
    '''
    self._obj = _scorer()
    self._score = dict()

  def _check_params (self, true, pred):
    '''
    Check input dimension shapes

    Parameters
    ----------
      true : array-like
        True label array

      pred : array-like
        Predicted label array
    '''
    if len(true) != len(pred):
      class_name = self.__class__.__name__
      raise ValueError('{0}: wrong shapes found. '
        'Found {1} true labels and {2} predicted labels. '
        'Input arrays must have the same length'.format(class_name, len(true), len(pred)))


  def _label2numbers (self, arr):
    '''
    Convert labels to numerical values

    Parameters
    ----------
      arr : array_like
        The array of labels

    Returns
    -------
      numeric_labels : np.ndarray
        Array of numerical labels obtained by the LabelEncoder transform

    Notes
    -----
      The C++ function allows only numerical (integer) values as labels in input.
      For more general support refers to the C++ example.
    '''
    unique = tuple(set(arr))

    if len(unique) <= 1:
      raise ValueError('The number of classes must be greater than 1')

    numeric_labels = np.array([unique.index(x) for x in arr])
    return numeric_labels

  def evaluate (self, lbl_true, lbl_pred):
    '''
    Evaluate scores of prediction labels vs true labels

    Parameters
    ----------
      lbl_true : array-like
        List of true labels

      lbl_pred : array-like
        List of predicted labels

    Returns
    -------
    self

    Notes
    -----
    The score evaluation is possible only with integer labels.
    The input labels are encoded in integers using LabelEncoder class of sklearn
    '''

    self._check_params(lbl_true, lbl_pred)

    y_true = self._label2numbers(lbl_true).astype('int32')
    y_pred = self._label2numbers(lbl_pred).astype('int32')

    # set contiguous order memory for c++ compatibility
    y_true = np.ascontiguousarray(y_true)
    y_pred = np.ascontiguousarray(y_pred)

    self._score = self._obj.evaluate(y_true, y_pred, len(y_true))
    self._score['Confusion Matrix'] = np.reshape(self._score['Confusion Matrix'], newshape=(len(self._score['classes']), len(self._score['classes'])))

    return self

  @property
  def score (self):
    '''
    Return the score list as dictionary
    '''
    return self._score

  @property
  def num_classes (self):
    '''
    Return number of classes identified
    '''
    return len(self._score['classes']) if 'classes' in self._score else 0

  def __getitem__ (self, stat):

    if not len(self._score):
      class_name = self.__class__.__name__
      raise ValueError('{0}: score not computed yet. Please use the "evaluate" method before'.format(class_name))

    try:

      return self._score[stat]

    except KeyError:
      class_name = self.__class__.__name__
      raise KeyError('{0}: statistic not found. Available statistics are {1}'.format(class_name, ','.join(self._score.keys())))

  def __setitem__ (self, stat, values):
    warnings.warn(UserWarning('Setting new statistics does not enable the computation of the dependencies'))
    self._score[stat] = values

  def __repr__ (self):
    return str(self._obj)

  def __str__ (self):

    fmt = ''

    fmt += 'Classes: {}\n'.format(', '.join(['{:d}'.format(int(c)) for c in self._score['classes']]))
    fmt += 'Confusion Matrix:\n'
    fmt += '\n'.join([''.join(['{:4}'.format(item) for item in row])
                      for row in self._score['Confusion Matrix']])

    fmt += '\n\nClass Statistics:\n\n'

    numeric_fmt = ' '.join(['{:>20.3f}' for _ in range(len(self._score['classes']))])
    array_fmt   = ' '.join(['{:>20}'    for _ in range(len(self._score['classes']))])

    for k, v in self._score.items():
      if isinstance(v, list) and k not in ['classes', 'Confusion Matrix']:
        try:
          fmt += '{name:<80} {value}\n'.format(**{'name' : k, 'value' : numeric_fmt.format(*v)})

        except ValueError:
          fmt += '{name:<80} {value}\n'.format(**{'name' : k, 'value' : array_fmt.format(*v)})


    fmt += '\nOverall Statistics:\n\n'

    for k, v in self._score.items():
      if not isinstance(v, list) and k not in ['classes', 'Confusion Matrix']:
        try:
          fmt += '{name:<80} {value:.3f}\n'.format(**{'name' : k, 'value' : v})
        except (ValueError, TypeError):
          fmt += '{name:<80} {value}\n'.format(**{'name' : k, 'value' : v})

    return fmt


if __name__ == '__main__':


  y_true = [2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2] # np.array([2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2], dtype=np.int32)
  y_pred = [0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2] # np.array([0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2], dtype=np.int32)

  scorer = Scorer()
  scorer.evaluate(y_true, y_pred)

  print(scorer)