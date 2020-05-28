#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
from __future__ import print_function

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']

def header ():
  return '\n'.join(('#ifndef __scorer_h__',
                    '#define __scorer_h__',
                    '', ''))

def include_lib (libs):
  return '\n'.join(('#include <{}>'.format(lib) for lib in libs))

def header_file (dependency):

  deps = dependency.copy()
  deps.pop('classes')

  obj = '\n'.join(('', 'struct scorer', '{', ''))

  variables = '\n'.join(('\tstd :: unique_ptr < float[] > {};'.format(name)
                          if cppvar['file'] in ('common_stats.h', 'class_stats.h')
                          else '\tfloat {};'.format(name)
                          for name, cppvar in deps.items()))

  variables = '\n'.join((variables, '',
                         '\tstd :: vector < float > classes;', '',
                         '\tint Nclass;', ''))

  constructor = '\n'.join(('', '\tscorer ();', '', '\t~scorer () = default;', '', '\t// Members', ''))

  members = '\n'.join(('', '\tvoid compute_score (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred);',
                       '',
                       '', '\ttemplate < typename Os >', '\tvoid print_class_stats (Os & os);',
                       '',
                       '', '\ttemplate < typename Os >', '\tvoid print_overall_stats (Os & os);',
                       '',
                       '', '\tvoid print ();',
                       '',
                       '', '\tvoid dump (const std :: string & filename);',
                       '',
                       '', '\ttemplate < typename dtype >', '\tint * encoder (dtype * arr, const int & size);',
                       ''))

  tail = '\n'.join(('', '};', '', '', '#endif // __scorer_h__', '', ''))

  libs = include_lib(('memory',
                      'iostream',
                      'iomanip',
                      'fstream',
                      'cassert',
                      'vector',
                      'algorithm',
                      'iterator',
                      'unordered_set',
                      ))

  scripts = ''.join((header(), libs,
                     '\n\n\n',
                     obj,
                     variables,
                     constructor,
                     members,
                     tail))
  return scripts

def start_omp():
  return '\n'.join(('#ifdef _OPENMP',
                    '#pragma omp parallel',
                    '\t{',
                    '#endif',
                    '\n'
                    ))

def stop_omp():
  return '\n'.join(('#ifdef _OPENMP',
                    '\t} // end parallel section',
                    '#endif',
                    '\n'
                    ))

def start_omp_section():
  return '\n'.join(('#ifdef _OPENMP',
                    '#pragma omp sections',
                    '\t{',
                    '#endif',
                    '\n'
                    ))

def stop_omp_section():
  return '\n'.join(('#ifdef _OPENMP',
                    '\t}',
                    '#endif',
                    '\n'
                    ))

def parallel_func(output, params):
  params = ', '.join(('this->{}.get()'.format(x)
                      if t == '*'
                      else 'this->{}'.format(x)
                      for x, t in params))
  params = params.replace('this->classes.get()', 'this->classes.data()')
  params = params.replace('this->lbl_true.get()', 'lbl_true')
  params = params.replace('this->lbl_pred.get()', 'lbl_pred')
  params = params.replace('this->n_true', 'n_true')
  params = params.replace('this->n_pred', 'n_pred')
  params = params.replace('this->n_lbl', 'n_lbl')
  return '\n'.join(('#ifdef _OPENMP',
                    '#pragma omp section',
                    '#endif',
                    ' '.join(('\t\tthis->{0} = get_{0} ('.format(output), params, ');')),
                    '\n'
                    ))

def check_dimension():
  return '\n'.join(('\tif ( this->Nclass == 1 )',
                    '\t{',
                    '#ifdef _OPENMP',
                    '#pragma omp single',
                    '#endif',
                    '\t' * 2 + 'std :: cerr << "Nclass must be greater than 1" << std :: endl;',
                    '\t' * 2 + 'std :: exit(1);',
                    '\t}', ''))

def cpp_file (workflow):

  libs = include_lib(('scorer.hpp',
                      'common_stats.h',
                      'class_stats.h',
                      'overall_stats.h'))

  members = '\n'.join(('scorer :: scorer ()',
                       '{',
                       '}', '', '',
                       'void scorer :: compute_score (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred)',
                       '{',
                       '#ifdef __pythonic__',
                       '#ifdef _OPENMP',
                       '#pragma omp parallel',
                       '\t{',
                       '#endif',
                       '#endif',
                       '',
                       '\tassert (n_true == n_pred);',
                       '\tauto n_lbl = n_true;',
                       ''))

  for level, deps in workflow.items():
    members = ''.join((members,
                       start_omp_section(),
                       ''.join((parallel_func(name, cppvar['dependency'])
                                for name, cppvar in deps)),
                       stop_omp_section()
                       ))
    if level == 0:
      members = '\n'.join((members,
                           '\tthis->Nclass = static_cast < int >(classes.size());\n',
                           check_dimension()
                           ))

  members = '\n'.join((members,
                       '#ifdef __pythonic__',
                       '#ifdef _OPENMP',
                       '\t} // end computation function',
                       '#endif',
                       '#endif',
                       '', '',
                       '}', '', '', ''))

  return ''.join((libs,
                  '\n\n\n',
                  members))

def hpp_file (dependency):

  deps = dependency.copy()
  deps.pop('confusion_matrix')

  header = '\n'.join(['#ifndef __scorer_hpp__', '#define __scorer_hpp__', '', ''])

  libs = include_lib(['scorer.h'])

  regex_dump_array = '\n'.join(('\tos << std :: left << std :: setw(40) << "{tag}";',
                                '\tfor (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << {name}[i] << " ";',
                                '\tos << std :: endl;',
                                ''
                                ))
  regex_dump_value = '\tos << std :: left << std :: setw(40) << "{tag}" << std :: setw(20) << {name} << std :: endl;\n'


  members = '\n'.join(('template < typename Os >',
                       'void scorer :: print_class_stats (Os & os)',
                       '{', ''))

  printers = '\n'.join((regex_dump_array.format(name=name, tag=cppvar['label'])
                       for name, cppvar in deps.items()
                       if cppvar['file'] in ('common_stats.h', 'class_stats.h')))

  members = '\n'.join((members, printers,
                       '}', '', '', '',
                       'template < typename Os >',
                       'void scorer :: print_overall_stats (Os & os)',
                       '{',
                       ''))

  overall = '\n'.join(regex_dump_value.format(name=name, tag=cppvar['label'])
                      for name, cppvar in deps.items()
                      if cppvar['file'] in ('overall_stats.h'))

  members = '\n'.join((members, overall,
                       '}', '', '', '',
                       'void scorer :: print ()',
                       '{',
                       '\tthis->print_class_stats < std :: ostream >(std :: cout);',
                       '\tstd :: cout << std :: endl;',
                       '\tthis->print_overall_stats < std :: ostream >(std :: cout);',
                       '}', '',
                       'void scorer :: dump (const std :: string & filename)',
                       '{',
                       '\tstd :: ofstream os (filename + ".cl_stats");',
                       '\tos << "stats," << std :: endl;',
                       '\tthis->print_class_stats < std :: ofstream >(os);',
                       '\tos.close();',
                       '',
                       '\tos.open(filename + ".overall_stats");',
                       '\tos << "stats,score" << std :: endl;',
                       '\tthis->print_overall_stats < std :: ofstream >(os);',
                       '\tos.close();',
                       '}', '',
                       ''
                       'template < typename dtype >',
                       'int * scorer :: encoder (dtype * arr, const int & size)',
                       '{', '',
                       '\tint * encode = new int [size];',
                       '',
                       '\tstd :: unordered_set < dtype > lbl (arr, arr + size, size * sizeof(dtype));',
                       '',
                       '\tstd :: transform (arr, arr + size, encode, [&](const dtype & l) {return std :: distance(lbl.begin(), lbl.find(l));});',
                       '',
                       '\treturn encode;',
                       '}', '',
                       ))

  tail = '\n'.join(('', '', '#endif // __scorer_hpp__', '', ''))

  return ''.join((header, libs,
                  '\n\n\n',
                  members,
                  tail))



if __name__ == '__main__':

  import os

  from dependency_graph import functions_script
  from dependency_graph import dependency_net
  from dependency_graph import workflow_net

  include_dir = os.path.join(os.path.dirname(__file__), '..', 'include/')
  src_dir     = os.path.join(os.path.dirname(__file__), '..', 'src/')

  dependency = {}
  for hpp in ('common_stats.h', 'class_stats.h', 'overall_stats.h'):
    dep = functions_script(include_dir + hpp)
    dependency.update(dep)

  dep_net = dependency_net(dependency)
  workflow = workflow_net(dep_net, dependency)

  header_script = header_file(dependency)
  hpp_script = hpp_file(dependency)
  cpp_script = cpp_file(workflow)

  header_file = os.path.join(include_dir, 'scorer.h')
  hpp_file = os.path.join(include_dir, 'scorer.hpp')
  cpp_file = os.path.join(src_dir, 'scorer.cpp')

  with open(header_file, 'w') as cpp:
    cpp.write(header_script)

  with open(hpp_file, 'w') as cpp:
    cpp.write(hpp_script)

  with open(cpp_file, 'w') as cpp:
    cpp.write(cpp_script)
