#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
from __future__ import print_function

import numpy as np
import warnings

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']


class Scorer (dict):
  '''
  Multi-class score computation.

  This class represents an optimized and extended version of the PyCM_ library.
  The full list of scores are evaluated using C++ functions wrapped into a single
  score object.
  The evaluation of the score functions can be performed into a parallel environment
  using OMP multhithreading.
  The C++ code is in fact auto-generated using the scripts provided into the utils_
  directory and the optimal dependency graph is computed to allow the work distribution
  among the available threads.

  Example
  -------
  >>> from scorer import Scorer
  >>>
  >>> y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
  >>> y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']
  >>>
  >>> scorer = Scorer()
  >>> scorer.evaluate(y_true, y_pred)

  References
  ----------
  - Haghighi, S., Jasemi, M., Hessabi, S. and Zolanvari, A. (2018). PyCM: Multiclass confusion matrix library in Python. Journal of Open Source Software, 3(25), p.729.

  .. _PyCM : https://github.com/sepandhaghighi/pycm
  .. _utils : https://github.com/Nico-Curti/scorer/blob/master/utils/
  '''

  def __init__ (self):
    '''
    Default constructor
    '''

    from scorer.lib.scorer import _scorer

    self._obj = _scorer()
    super(Scorer, self).__init__({})

  def _check_params (self, true, pred):
    '''
    Check input dimension shapes

    Parameters
    ----------
      true : array-like
        True label array

      pred : array-like
        Predicted label array

    Notes
    -----
    .. note::
      The array of true labels and predicted ones mush have the same length.
      If the given arrays have different shapes a ValueError is raised.
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
      .. note::
        The C++ function allows only numerical (integer) values as labels in input.
        For more general support refers to the C++ example.

    Examples
    --------
    >>> from scorer import scorer
    >>> y = ('A', 'A', 'B', 'B')
    >>> num_y = scorer()._label2numbers(y)
    >>> print(num_y)
      [0, 0, 1, 1]
    '''
    unique, numeric_labels = np.unique(arr, return_inverse=True)

    if unique.size <= 1:
      raise ValueError('The number of classes must be greater than 1')

    return numeric_labels.astype('int32'), unique

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

    Examples
    --------
    >>> from scorer import scorer
    >>> size = 10
    >>> y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>> y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>>
    >>> scorer = Scorer()
    >>> scorer.evaluate(y_true, y_pred)
    >>>
    >>> # Or using simple lists
    >>>
    >>> y_true = y_true.tolist()
    >>> y_pred = y_pred.tolist()
    >>>
    >>> scorer.evaluate(y_true, y_pred)

    Notes
    -----
    .. note::
      The score evaluation is possible only with integer labels.
      The input labels are encoded in integers using the C++ version of the label encoder (_label2numbers).
    '''

    self._check_params(lbl_true, lbl_pred)

    y_true, true_names = self._label2numbers(lbl_true)
    y_pred, true_names = self._label2numbers(lbl_pred)

    # set contiguous order memory for c++ compatibility
    y_true = np.ascontiguousarray(y_true)
    y_pred = np.ascontiguousarray(y_pred)

    score = self._obj.evaluate(y_true, y_pred, len(y_true))
    self.update(score)

    with warnings.catch_warnings():
      warnings.simplefilter("ignore")
      self['Confusion Matrix'] = np.reshape(self['Confusion Matrix'], newshape=(len(self['classes']), len(self['classes'])))
      self['classes'] = true_names

    return self

  @property
  def score (self):
    '''
    Return the score list as dictionary.
    '''
    return self

  @property
  def num_classes (self):
    '''
    Return the number of classes identified.
    If the scores are not yet evaluated the return value is 0.
    '''
    return len(self['classes']) if 'classes' in self else 0

  @property
  def _get_available_metrics (self):
    '''
    Get the dictionary of available metrics in a more manageable format.
    '''
    return self._obj.get_available_metrics

  def __getattr__ (self, stat):
    '''
    Access to score stats as attribute

    Parameters
    ----------
      stat: name
        Name of the score

    Examples
    --------
    >>> from scorer import scorer
    >>> size = 10
    >>> y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>> y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>>
    >>> scorer = Scorer()
    >>> scorer.evaluate(y_true, y_pred)
    >>> print(scorer.ACC, scorer.TP, scorer.FP)

    Notes
    -----
    .. note::
      In many cases the string related to the score is very long and it includes
      information about the mathematical meaning of that score.
      To facilitate the usage of the class the search of the attributes is performed
      using a "regex" search.
      In this way it is possible to access member values as in the following example

      .. code-block:: python

        np.testing.assert_allclose(scorer['ACC(Accuracy)'], scorer.ACC)
        np.testing.assert_allclose(scorer['FP(False positive/type 1 error/false alarm)'], scorer.FP)
        np.testing.assert_allclose(scorer['TOP(Test outcome positive)'], scorer.TOP)
        np.testing.assert_allclose(scorer['FDR(False discovery rate)'], scorer.FDR)

      If the attribute is not found an AttributeError is raised.
    '''

    if stat in self._get_available_metrics:
      stat = self._get_available_metrics[stat]
      return self[stat]

    elif stat in self:
      return self[stat]

    else:

      for x in sorted(self.keys()):
        y = x.split('(')[0]
        y = y.replace('%', '')
        y = y.replace(' ', '_')
        y = y.replace('-', '_')
        if y == stat:
          return super(Scorer, self).__getitem__(x)

      else:
        raise AttributeError('Attribute {} not found'.format(stat))

  def __getitem__ (self, stat):
    '''
    Get the value of the required score

    Parameters
    ----------
      stat: str
        Name of the score

    Examples
    --------
    >>> from scorer import scorer
    >>> size = 10
    >>> y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>> y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>>
    >>> scorer = Scorer()
    >>> scorer.evaluate(y_true, y_pred)
    >>>
    >>> print(scorer['accuracy_score'])

    Notes
    -----
    .. note::
      The search of the score name is performed using the key name of the dictionary.
      This function is different from __getattr__.
    '''

    if not len(self):
      class_name = self.__class__.__name__
      raise ValueError('{0}: score not computed yet. Please use the "evaluate" method before'.format(class_name))

    try:

      return super(Scorer, self).__getitem__(stat)

    except KeyError:

      stat = self._get_available_metrics[stat]
      return self[stat]

    except KeyError:
      class_name = self.__class__.__name__
      raise KeyError('{0}: statistic not found. Available statistics are {1}'.format(class_name, ','.join(self.keys())))

  def __setitem__ (self, stat, values):
    '''
    Set a score variable.

    Parameters
    ----------
      stat: str
        Key as name of the new score

      values: float or list
        Value(s) of the new score

    Examples
    --------
    >>> from scorer import scorer
    >>> size = 10
    >>> y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>> y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    >>>
    >>> scorer = Scorer()
    >>> scorer.evaluate(y_true, y_pred)
    >>>
    >>> scorer['dummy'] = 'dummy'
      UserWarning: Setting new statistics does not enable the computation of the dependencies
    '''
    warnings.warn(UserWarning('Setting new statistics does not enable the computation of the dependencies'))
    super(Scorer, self).__setitem__(stat, values)

  def __repr__ (self):
    '''
    Object representation
    '''
    return str(self._obj)

  def __str__ (self):
    '''
    Print the object as table of scores
    '''
    fmt = ''

    fmt += 'Classes: {}\n'.format(', '.join(['{}'.format(c) for c in self['classes']]))
    fmt += 'Confusion Matrix:\n'
    fmt += '\n'.join([''.join(['{:4}'.format(item) for item in row])
                      for row in self['Confusion Matrix']])

    fmt += '\n\nClass Statistics:\n\n'

    numeric_fmt = ' '.join(['{:>20.3f}' for _ in range(len(self['classes']))])
    array_fmt   = ' '.join(['{:>20}'    for _ in range(len(self['classes']))])

    for k, v in self.items():
      if isinstance(v, list) and k not in ['classes', 'Confusion Matrix']:
        try:
          fmt += '{name:<80} {value}\n'.format(**{'name' : k, 'value' : numeric_fmt.format(*v)})

        except ValueError:
          fmt += '{name:<80} {value}\n'.format(**{'name' : k, 'value' : array_fmt.format(*v)})


    fmt += '\nOverall Statistics:\n\n'

    for k, v in self.items():
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
