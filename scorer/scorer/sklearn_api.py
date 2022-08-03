#!/usr/bin/env python
# -*- coding: utf-8 -*-

from scorer import Scorer
from sklearn.metrics._classification import _check_targets

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']
__all__ = ['score_metrics']


def score_metrics (y_true, y_pred, metrics=['accuracy_score']):
  '''
  Scikit-learn compatibility API for Scorer usage.
  Evaluate the required score-metric using the Scorer object.

  Parameters
  ----------
    y_true : array-like
      List of true labels

    y_pred : array-like
      List of predicted labels

    metrics : str or array-like
      List of metric-names to evaluate

  Returns
  -------
    metrics : float or array-like
      The required metrics

  Example
  -------
  >>> from scorer import sklearn_api
  >>>
  >>> y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
  >>> y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']
  >>>
  >>> metrics = sklearn_api.score_metrics(y_true, y_pred, metrics='accuracy_score')

  Or you can use the scorer metrics inside a sklearn pipeline like

  Example
  -------
  >>> from scorer import sklearn_api
  >>> from sklearn.svm import SVC
  >>> from sklearn.metrics import make_scorer
  >>> from sklearn.model_selection import cross_val_score
  >>> from sklearn.datasets import load_iris
  >>>
  >>> X, y = load_iris(return_X_y=True)
  >>> clf = SVC(kernel='linear', C=1.)
  >>> my_scorer = make_scorer(sklearn_api.score_metrics, metrics='accuracy_score')
  >>>
  >>>  scores = cross_val_score(clf,  # classifier
  >>>                           X,  # training data
  >>>                           y,  # training labels
  >>>                           cv=5,  # split data randomly into 10 parts: 9 for training, 1 for scoring
  >>>                           scoring=my_scorer,  # which scoring metric?
  >>>                          )
  '''

  y_type, y_true, y_pred = _check_targets(y_true, y_pred)

  if y_type not in {'binary', 'multiclass'}:
    raise ValueError('{0} is not supported'.format(y_type))

  scorer = Scorer()
  available_metrics = scorer._get_available_metrics

  # convert str to iterable
  if isinstance(metrics, str):
    metrics = [metrics]

  # check metric params

  if not all(metric in available_metrics for metric in metrics):
    raise ValueError('score_metrics error: metric {0} not found. \
                      Available metrics are {1}'.format(
                      metrics, ','.join(available_metrics)))

  scorer.evaluate(y_true, y_pred)

  metrics = [available_metrics[metric] for metric in metrics]
  results = [scorer[metric] for metric in metrics]

  return results if len(results) > 1 else results[0]
