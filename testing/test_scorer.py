#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from io import StringIO

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
  def test_with_input_list (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    y_true = y_true.tolist()
    y_pred = y_pred.tolist()

    scorer = Scorer()
    _ = scorer.evaluate(y_true, y_pred)

    assert isinstance(_, type(scorer))
    assert repr(scorer) == '<Scorer (classes: 2)>'

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_with_input_numpy (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer = Scorer()
    _ = scorer.evaluate(y_true, y_pred)

    assert isinstance(_, type(scorer))
    assert repr(scorer) == '<Scorer (classes: 2)>'

  @given(size = st.integers(min_value=5, max_value=50))
  @settings(max_examples=10, deadline=None)
  def test_print (self, size):

    y_true = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))
    y_pred = np.random.choice([0., 1.], p=[.5, .5], size=(size, ))

    scorer = Scorer()
    _ = scorer.evaluate(y_true, y_pred)

    stdout = StringIO()
    sys.stdout = stdout
    print(scorer)
    sys.stdout = sys.__stdout__

    printed = stdout.getvalue().splitlines()

    assert printed[0] == 'Classes: 0.0, 1.0'

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

    scorer.evaluate(y_true, y_pred)

    assert scorer.num_classes == 2

    np.testing.assert_allclose(scorer['FP(False positive/type 1 error/false alarm)'], np.zeros(shape=(len(set(y_true)), )))
    np.testing.assert_allclose(scorer.score['FN(False negative/miss/type 2 error)'], np.zeros(shape=(len(set(y_true)), )))
    np.testing.assert_allclose(scorer.score['ACC(Accuracy)'], np.ones(shape=(len(set(y_true)), )))

  def test_getter_error_before_fit (self):

    size = 10
    y_true = [1]*size
    y_pred = [1]*size
    y_true.append(0)
    y_pred.append(0)

    scorer = Scorer()

    with pytest.raises(ValueError):
      print(scorer['ACC(Accuracy)'])

  def test_getter_error_wrong_key (self):

    size = 10
    y_true = [1]*size
    y_pred = [1]*size
    y_true.append(0)
    y_pred.append(0)

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)

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

  def test_setter_warning (self):

    scorer = Scorer()

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

  def test_getter_alias_error (self):

    y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
    y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)

    with pytest.raises(AttributeError):
      scorer.dummy

  def test_lut_alias (self):

    y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
    y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)

    np.testing.assert_allclose(scorer['ACC(Accuracy)'], scorer['class_accuracy'])
    np.testing.assert_allclose(scorer['FP(False positive/type 1 error/false alarm)'], scorer['class_false_positive'])
    np.testing.assert_allclose(scorer['TOP(Test outcome positive)'], scorer['class_test_outcome_positive'])
    np.testing.assert_allclose(scorer['FDR(False discovery rate)'], scorer['class_false_discovery_rate'])

    np.testing.assert_allclose(scorer['Overall ACC'], scorer['accuracy_score'])

  def test_lut_alias_error (self):

    y_true = ['a', 'b', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'b', 'c', 'a']
    y_pred = ['b', 'b', 'a', 'c', 'b', 'a', 'c', 'b', 'a', 'b', 'a', 'a']

    scorer = Scorer()
    scorer.evaluate(y_true, y_pred)

    with pytest.raises(KeyError):
      scorer['dummy']
