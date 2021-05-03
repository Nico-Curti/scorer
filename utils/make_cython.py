#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
from __future__ import print_function

import re
import os

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']


def make_base_pyx_script ():

  body = '''# distutils: language = c++
# cython: language_level=2

from cython.operator cimport dereference as deref
from libcpp.memory cimport unique_ptr

from scorer cimport scorer

cdef class _scorer:

  def __init__ (self):
    self.thisptr.reset(new scorer())


  def evaluate (self, int[::1] lbl_true, int[::1] lbl_pred, int n_lbl):
    deref(self.thisptr).compute_score(&lbl_true[0], &lbl_pred[0], n_lbl, n_lbl)

    self.Nclass = deref(self.thisptr).classes.size()

    score = {{
{0}
            }}

    _mcc_analysis = ['Negligible', 'Weak', 'Moderate', 'Strong', 'Very Strong', 'None']
    _nlr_analysis = ['Good', 'Fair', 'Poor', 'Negligible', 'None']
    _plr_analysis = ['Negligible', 'Poor', 'Fair', 'Good', 'None']
    _dp_analysis  = ['Poor', 'Limited', 'Fair', 'None']
    _auc_analysis = ['Poor', 'Fair', 'Good', 'Very Good', 'Excellent', 'None']
    _V_analysis   = ['Negligible', 'Weak', 'Moderate', 'Relatively Strong', 'Strong', 'Very Strong', 'None']
    _kcicchetti_analysis = ['Poor', 'Fair', 'Good', 'Excellent', 'None']
    _kkoch_analysis      = ['Poor', 'Slight', 'Fair', 'Moderate', 'Substantial', 'Almost Perfect', 'None']
    _kfleiss_analysis    = ['Poor', 'Intermediate to Good', 'Excellent', 'None']
    _kaltman_analysis    = ['Poor', 'Fair', 'Moderate', 'Good', 'Very Good', 'None']

    score['SOA1(Landis & Koch)'] = _kkoch_analysis[     int(score['SOA1(Landis & Koch)'])]
    score['SOA2(Fleiss)'       ] = _kfleiss_analysis[   int(score['SOA2(Fleiss)'])]
    score['SOA3(Altman)'       ] = _kaltman_analysis[   int(score['SOA3(Altman)'])]
    score['SOA4(Cicchetti)'    ] = _kcicchetti_analysis[int(score['SOA4(Cicchetti)'])]
    score['SOA5(Cramer)'       ] = _V_analysis[         int(score['SOA5(Cramer)'])]
    score['SOA6(Matthews)'     ] = _mcc_analysis[       int(score['SOA6(Matthews)'])]

    score['NLRI(Negative likelihood ratio interpretation)'] = [_nlr_analysis[int(item)] for item in score['NLRI(Negative likelihood ratio interpretation)']]
    score['PLRI(Positive likelihood ratio interpretation)'] = [_plr_analysis[int(item)] for item in score['PLRI(Positive likelihood ratio interpretation)']]
    score['AUCI(AUC value interpretation)'] = [_auc_analysis[int(item)] for item in score['AUCI(AUC value interpretation)']]
    score['DPI(Discriminant power interpretation)' ] = [_dp_analysis[int(item)] for item in score['DPI(Discriminant power interpretation)' ]]
    score['MCCI(Matthews correlation coefficient interpretation)'] = [_mcc_analysis[int(item)] for item in score['MCCI(Matthews correlation coefficient interpretation)']]

    return score

  @property
  def get_available_metrics (self):
    return {{
{1}
           }}

  @property
  def num_classes (self):
    return deref(self.thisptr).classes.size()

  def __repr__ (self):
    return '<Scorer (classes: {{0}})>'.format(self.num_classes)
  '''

  return body

def make_base_pxd_script ():

  body = '''# distutils: language = c++
# cython: language_level=2

from libcpp.vector cimport vector
from libcpp.memory cimport unique_ptr

cdef extern from "scorer.h":

  cppclass scorer:

    scorer() except +

    # Attributes

{0}

    # Methods
    void compute_score(int *, int *, int, int)
    void print_class_stats[T](T&)
    void print_overall_stats[T](T&)


cdef extern from "<utility>" namespace "std" nogil:

  cdef unique_ptr[scorer] move(unique_ptr[scorer])


cdef class _scorer:

  cdef unique_ptr[scorer] thisptr

  cdef public:
    int Nclass
  '''
  return body


def load_sklearn_lut ():

  lut_file = os.path.join(os.path.dirname(__file__), 'sklearn_lut.conf')
  line = re.compile(r'(?P<name>\w+)\s*[=:]\s*\'(?P<value>.*)\'')

  with open(lut_file, 'r') as fp:
    lut = fp.read()

  lut = line.findall(lut)
  return lut


if __name__ == '__main__':

  from dependency_graph import functions_script
  from dependency_graph import dependency_net
  from dependency_graph import workflow_net

  include_dir = os.path.join(os.path.dirname(__file__), '..', 'include/')
  src_dir     = os.path.join(os.path.dirname(__file__), '..', 'src/')
  pyx_dir     = os.path.join(os.path.dirname(__file__), '..', 'scorer/source/')
  pxd_dir     = os.path.join(os.path.dirname(__file__), '..', 'scorer/lib/')

  dependency = {}
  for hpp in ('common_stats.h', 'class_stats.h', 'overall_stats.h'):
    dep = functions_script(include_dir + hpp)
    dependency.update(dep)

  pyx_variables = []
  pxd_variables = []

  row_array    = '              \'{1}\' : [(deref(self.thisptr).{0}.get())[i] for i in range(self.Nclass)],'
  row_variable = '              \'{1}\' : deref(self.thisptr).{0},'

  for variable, labels in dependency.items():
    long_name_description = labels['label']
    script = labels['file']

    # Special cases
    if variable == 'classes':
      pyx_row = '              \'{1}\': deref(self.thisptr).{0},'.format(variable, long_name_description)
      pxd_row = '    vector[float] {0}'.format(variable)

    elif variable == 'confusion_matrix':
      pyx_row = '              \'{1}\': [int((deref(self.thisptr).{0}.get())[i]) for i in range(self.Nclass * self.Nclass)],'.format(variable, long_name_description)
      pxd_row = '    unique_ptr[float] {0}'.format(variable)

    # Special multiple cases

    elif variable == 'TPR_PPV_F1_micro':
      pyx_row = '\n'.join(['              \'TPR Micro\' : deref(self.thisptr).TPR_PPV_F1_micro,',
                           '              \'PPV Micro\' : deref(self.thisptr).TPR_PPV_F1_micro,',
                           '              \'F1 Micro\' : deref(self.thisptr).TPR_PPV_F1_micro,',
                           ])
      pxd_row = '    float TPR_PPV_F1_micro'

    # Special Tuple cases

    elif variable == 'kappa_CI_up':
      pyx_row = '              \'Kappa 95% CI\': (deref(self.thisptr).kappa_CI_up, deref(self.thisptr).kappa_CI_down),'
      pxd_row = '\n'.join(['    float kappa_CI_up', '    float kappa_CI_down'])

    elif variable == 'overall_accuracy_ci_up':
      pyx_row = '              \'95% CI\': (deref(self.thisptr).overall_accuracy_ci_up, deref(self.thisptr).overall_accuracy_ci_down),'
      pxd_row = '\n'.join(['    float overall_accuracy_ci_up', '    float overall_accuracy_ci_down'])

    elif variable == 'overall_jaccard_index':
      pyx_row = '              \'Overall J\': (deref(self.thisptr).overall_jaccard_index, deref(self.thisptr).overall_jaccard_index / self.Nclass),'
      pxd_row = '    float overall_jaccard_index'

    # Skip duplicates (due to tuple)

    elif variable in ('kappa_CI_down', 'overall_accuracy_ci_down', 'overall_jaccard_index'): # skip counterpart of tuples
      continue

    # Skip useless variables

    elif variable in ('PC_PI', 'PC_AC1', 'PC_S'):
      continue

    # Standard cases

    elif script == 'overall_stats.h': # it is an overall score and thus a single variable
      pyx_row = row_variable.format(variable, long_name_description)
      pxd_row = '    float {0}'.format(variable)

    elif script in ('class_stats.h', 'common_stats.h'): # it is a class score and thus an array variable
      pyx_row = row_array.format(variable, long_name_description)
      pxd_row = '    unique_ptr[float] {0}'.format(variable)

    pyx_variables.append(pyx_row)
    pxd_variables.append(pxd_row)


  sklearn_lut = load_sklearn_lut()
  sklearn_lut = '\n'.join(['             \'{0}\' : \'{1}\','.format(var, description) for var, description in sklearn_lut])


  cython_pyx_file = os.path.join(pyx_dir, 'scorer.pyx')
  cython_pxd_file = os.path.join(pxd_dir, 'scorer.pxd')

  with open(cython_pyx_file, 'w') as pyx:
    body = make_base_pyx_script()
    pyx.write(body.format('\n'.join(pyx_variables), sklearn_lut))

  with open(cython_pxd_file, 'w') as pxd:
    body = make_base_pxd_script()
    pxd.write(body.format('\n'.join(pxd_variables)))
