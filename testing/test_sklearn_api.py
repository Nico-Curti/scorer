#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
from scorer import Scorer
from scorer import sklearn_api

import sklearn.metrics as sk
from sklearn.svm import SVC
from sklearn.metrics import make_scorer
from sklearn.model_selection import cross_val_score
from sklearn.datasets import load_iris

import pytest
from hypothesis import strategies as st
from hypothesis import given
from hypothesis import settings

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']


class TestSklearnAPI:

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_error_metrics (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    y_true = y_true.tolist()
    y_pred = y_pred.tolist()

    metric = 'dummy'

    with pytest.raises(ValueError):
      sklearn_api.score_metrics(y_true, y_pred, metrics=metric)

    metric = ['accuracy_score', 'dummy']

    with pytest.raises(ValueError):
      sklearn_api.score_metrics(y_true, y_pred, metrics=metric)


  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_error_type_labels (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, 2)).astype(int)
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, 2)).astype(int)

    # multiclass-multioutput type
    with pytest.raises(ValueError):
      sklearn_api.score_metrics(y_true, y_pred, metrics='accuracy_score')

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, 2))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, 2))

    # continuous-multioutput type
    with pytest.raises(ValueError):
      sklearn_api.score_metrics(y_true, y_pred, metrics='accuracy_score')

  def test_metric (self):

    y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
    y_pred = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']

    accuracy = sklearn_api.score_metrics(y_true, y_pred, metrics='accuracy_score')

    assert accuracy == 1

  @given(size = st.integers(min_value=5, max_value=50),
         metric = st.sampled_from(['accuracy_score',
                                   'hamming_loss',
                                   'cohen_kappa_score',
                                   'confusion_matrix',
                                   'matthews_corrcoef',
                                   ]
                                  )
         )
  @settings(max_examples=10, deadline=None)
  def test_sklearn_metrics (self, size, metric):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics=metric)
    sklearn_res = getattr(sk, metric)(y_true, y_pred)

    if hasattr(scorer_res, '__iter__'):
      np.testing.assert_allclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)

    else:
      assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)


  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_sklearn_zero_one_loss (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='zero_one_loss')
    sklearn_res = sk.zero_one_loss(y_true, y_pred, normalize=False)

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_sklearn_jaccard_score (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='jaccard_score')[1]
    sklearn_res = sk.jaccard_score(y_true, y_pred, average='macro')

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_sklearn_f1_score (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='f1_macro')
    sklearn_res = sk.f1_score(y_true, y_pred, average='macro')

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='f1_micro')
    sklearn_res = sk.f1_score(y_true, y_pred, average='micro')

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)


  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_sklearn_recall (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='recall_macro')
    sklearn_res = sk.recall_score(y_true, y_pred, average='macro')

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='recall_micro')
    sklearn_res = sk.recall_score(y_true, y_pred, average='micro')

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_sklearn_precision (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='precision_macro')
    sklearn_res = sk.precision_score(y_true, y_pred, average='macro')

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)

    scorer_res = sklearn_api.score_metrics(y_true, y_pred, metrics='precision_micro')
    sklearn_res = sk.precision_score(y_true, y_pred, average='micro')

    assert np.isclose(scorer_res, sklearn_res, rtol=1e-05, atol=1e-5)


  def test_sklearn_compatibility (self):

    X, y = load_iris(return_X_y=True)
    clf = SVC(kernel='linear', C=1.)
    my_scorer = make_scorer(sklearn_api.score_metrics, metrics='accuracy_score')

    scores = cross_val_score(clf,  # classifier
                             X,  # training data
                             y,  # training labels
                             cv=5,  # split data randomly into 10 parts: 9 for training, 1 for scoring
                             scoring=my_scorer,  # which scoring metric?
                            )
