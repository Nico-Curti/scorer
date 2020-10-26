#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
from __future__ import print_function

import numpy as np
from scorer import Scorer

import pytest
from hypothesis import strategies as st
from hypothesis import given
from hypothesis import settings

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']


class TestScorer:

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_list (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    y_true = y_true.tolist()
    y_pred = y_pred.tolist()

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)
    print(scorer)
    repr(scorer)

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_numpy (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)
    print(scorer)
    repr(scorer)

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_wrong_size (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size + 1, ))

    scorer = Scorer()

    with pytest.raises(ValueError):
      scorer.evaluate(y_true, y_pred)

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_getter (self, size):

    y_true = [1]*size
    y_pred = [1]*size
    y_true.append(0)
    y_pred.append(0)

    scorer = Scorer()

    with pytest.raises(ValueError):
      print(scorer['ACC(Accuracy)'])

    scorer.evaluate(y_true, y_pred)

    assert scorer.num_classes == 2

    np.testing.assert_allclose(scorer['FP(False positive/type 1 error/false alarm)'], np.zeros(shape=(len(set(y_true)), )))
    np.testing.assert_allclose(scorer.score['FN(False negative/miss/type 2 error)'], np.zeros(shape=(len(set(y_true)), )))
    np.testing.assert_allclose(scorer.score['ACC(Accuracy)'], np.ones(shape=(len(set(y_true)), )))


    np.testing.assert_allclose(scorer.score['Overall ACC'], scorer.score['accuracy_score'])

    with pytest.raises(KeyError):
      print(scorer['dummy'])

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_wrong_nclass (self, size):

    y_true = [1]*size
    y_pred = [1]*size

    scorer = Scorer()

    with pytest.raises(ValueError):
      scorer.evaluate(y_true, y_pred)

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_setter (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)

    with pytest.warns(UserWarning):
      scorer['Nico'] = 'Nico'

  def test_encoder (self):

    y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
    y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)
    str_score = scorer.score

    y_true = [2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2]
    y_pred = [0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2]

    scorer.evaluate(y_true, y_pred)
    num_score = scorer.score

    assert str_score == num_score

  def test_keys (self):

    y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
    y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']

    scorer = Scorer()
    assert len(scorer.keys()) == 0

    scorer.evaluate(y_true, y_pred)
    assert len(scorer.keys()) == 116

  def test_getter_alias (self):

    y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
    y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)

    np.testing.assert_allclose(scorer['ACC(Accuracy)'], scorer.ACC)
    np.testing.assert_allclose(scorer['FP(False positive/type 1 error/false alarm)'], scorer.FP)
    np.testing.assert_allclose(scorer['TOP(Test outcome positive)'], scorer.TOP)
    np.testing.assert_allclose(scorer['FDR(False discovery rate)'], scorer.FDR)

    np.testing.assert_allclose(scorer['Overall ACC'], scorer.accuracy_score)
    np.testing.assert_allclose(scorer['FP(False positive/type 1 error/false alarm)'], scorer.class_false_positive)

    with pytest.raises(AttributeError):
      scorer.dummy
