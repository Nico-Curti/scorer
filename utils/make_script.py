#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
from __future__ import print_function

__package__ = 'Auto-generate Scorer object'
__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']

def header ():
  return '\n'.join(['#ifndef __scorer_h__', '#define __scorer_h__', '', ''])

def include_lib (libs):
  return '\n'.join(['#include <{}>'.format(lib) for lib in libs])

def header_file (dependencies):

  obj = '\n'.join(['', 'struct scorer', '{', ''])

  variables = '\n'.join(['', '\tstd :: vector < float > classes;', ''])

  variables += '\tstd :: unique_ptr < float[] > '
  variables += ', '.join([f for f in dependencies['common_stats.h'].keys() if f != 'classes'])
  variables += ', '
  variables += ', '.join([f for f in dependencies['class_stats.h'].keys()])
  variables += ';\n'
  variables += '\tfloat '
  variables += ', '.join([f for f in dependencies['overall_stats.h'].keys()])
  variables += ';\n\n'
  variables += '\n'.join(['\tint Nclass;', ''])

  constructor = '\n'.join(['', '\tscorer ();', '', '\t//Members', ''])

  members = '\n'.join(['', '\tvoid compute_score (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred);', ''])

  members += '\n'.join(['', '\ttemplate < typename Os >', '\tvoid print_class_stats (Os & os);', ''])
  members += '\n'.join(['', '\ttemplate < typename Os >', '\tvoid print_overall_stats (Os & os);', ''])
  members += '\n'.join(['', '\tvoid print ();', ''])
  members += '\n'.join(['', '\tvoid dump (const std :: string & filename);', ''])

  tail = '\n'.join(['', '};', '', '', '#endif // __scorer_h__', '', ''])

  libs = include_lib(['memory',
                      'iostream',
                      'iomanip',
                      'fstream',
                      'cassert',
                      'vector'
                      ])

  scripts = header() + libs + '\n\n\n' + obj + variables + constructor + members + tail
  return scripts

def start_omp():
  return '\n'.join(['#ifdef _OPENMP',
                    '#pragma omp parallel',
                    '\t{',
                    '#endif',
                    '\n'
                    ])

def stop_omp():
  return '\n'.join(['#ifdef _OPENMP',
                    '\t} // end parallel section',
                    '#endif',
                    '\n'
                  ])

def start_omp_section():
  return '\n'.join(['#ifdef _OPENMP',
                    '#pragma omp sections',
                    '\t{',
                    '#endif',
                    '\n'])

def stop_omp_section():
  return '\n'.join(['#ifdef _OPENMP',
                    '\t}',
                    '#endif',
                    '\n'])

def parallel_func(output, params):
  return '\n'.join(['#ifdef _OPENMP',
                    '#pragma omp section',
                    '#endif',
                    '\t\tthis->{0} = get_{0} ('.format(output) + ', '.join(params) + ');',
                    '\n'
                    ])

def check_dimension():
  return '\tif ( this->Nclass == 1 )\n' + \
         '\t{\n' + \
         '#ifdef _OPENMP\n#pragma omp single\n#endif\n' + \
         '\t' * 2 + 'std :: cerr << "Nclass must be greater than 1" << std :: endl;\n' + \
         '\t' * 2 + 'std :: exit(1);\n' + \
         '\t}\n\n'

def cpp_file (workflow):

  libs = include_lib(['scorer.hpp'])

  members  = 'scorer :: scorer ()\n{\n}\n'

  # compute score functions in parallel
  members += 'void scorer :: compute_score (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred)'
  members += '\n'
  members += '{'
  members += '\n'
  members += '#ifdef __pythonic__\n#ifdef _OPENMP\n#pragma omp parallel\n\t{\n#endif\n#endif\n'
  members += '\n'

  members += '\tassert (n_true == n_pred);'
  members += '\n'
  members += '\tauto n_lbl = n_true;'
  members += '\n'
  members += '\n'

  for lv, values in workflow.items():
    members += start_omp_section()
    for (_, output, params) in values:
      members += parallel_func(output, params)
    members += stop_omp_section()
    if lv == 0:
      members += '\tthis->Nclass = static_cast < int >(classes.size());\n\n'
      members += check_dimension()

  members += '#ifdef __pythonic__\n#ifdef _OPENMP\n\t}\n#endif\n#endif\n'
  members += '\t} // end computation function'
  members += '\n\n'

  members += '\n'.join(['}', '', '', ''])

  return libs + '\n\n\n' + members

def hpp_file (dependencies):

  header = '\n'.join(['#ifndef __scorer_hpp__', '#define __scorer_hpp__', '', ''])

  libs = include_lib(['scorer.h',
                      'common_stats.h',
                      'class_stats.h',
                      'overall_stats.h'])

  members = ''
  # dump members

  regex_dump_array = '\tos << std :: left << std :: setw(40) << "{name}";\n\tfor (int i = 0; i < this->Nclass; ++i) os << std :: setw(20) << {name}[i] << " ";\n\tos << std :: endl;'
  regex_dump_value = '\tos << std :: left << std :: setw(40) << "{name}" << std :: setw(20) << {name} << std :: endl;\n'


  members += 'template < typename Os >'
  members += '\n'
  members += 'void scorer :: print_class_stats (Os & os)'
  members += '\n'
  members += '{'
  members += '\n'

  for f in dependency['common_stats.h'].keys():
    if f != 'confusion_matrix':
      members += regex_dump_array.format(name=f)

  for f in dependency['class_stats.h'].keys():
    members += regex_dump_array.format(name=f)

  members += '\n'.join(['}', '', '', ''])

  members += 'template < typename Os >'
  members += '\n'
  members += 'void scorer :: print_overall_stats (Os & os)'
  members += '\n'
  members += '{'
  members += '\n'

  for f in dependencies['overall_stats.h'].keys():
    members += regex_dump_value.format(name=f)

  members += '\n'.join(['}', '', '', ''])

  members += 'void scorer :: print ()'
  members += '\n'
  members += '{'
  members += '\n'
  members += '\tthis->print_class_stats < std :: ostream >(std :: cout);'
  members += '\n'
  members += '\tstd :: cout << std :: endl;'
  members += '\n'
  members += '\tthis->print_overall_stats < std :: ostream >(std :: cout);'
  members += '\n'
  members += '}'
  members += '\n'
  members += '\n'

  members += 'void scorer :: dump (const std :: string & filename)'
  members += '\n'
  members += '{'
  members += '\n'
  members += '\tstd :: ofstream os (filename + ".cl_stats");'
  members += '\n'
  members += '\tos << "stats," << std :: endl;'
  members += '\n'
  members += '\tthis->print_class_stats < std :: ofstream >(os);'
  members += '\n'
  members += '\tos.close();'
  members += '\n'
  members += '\n'
  members += '\tos.open(filename + ".overall_stats");'
  members += '\n'
  members += '\tos << "stats,score" << std :: endl;'
  members += '\n'
  members += '\tthis->print_overall_stats < std :: ofstream >(os);'
  members += '\n'
  members += '\tos.close();'
  members += '\n'
  members += '}'
  members += '\n'
  members += '\n'

  tail = '\n'.join(['', '', '#endif // __scorer_hpp__', '', ''])

  return header + libs + '\n\n\n' + members + tail



if __name__ == '__main__':

  import os

  from dependency_graph import functions_script
  from dependency_graph import dependency_net
  from dependency_graph import workflow_net

  from collections import defaultdict


  directory = os.path.join(os.path.dirname(__file__), '..', 'include/')

  dependency = {hpp : functions_script(directory + hpp) for hpp in ['common_stats.h',
                                                                    'class_stats.h',
                                                                    'overall_stats.h'
                                                                    ]}


  all_deps = dict(pair for d in [v for i,v in dependency.items()] for pair in d.items())

  dep_net = dependency_net(all_deps)
  workflow = workflow_net(dep_net, dependency)

  utility = defaultdict(list)
  already_computed = dict()

  for s, v in workflow.items():
    for script, output, params in v:
      if script == 'common_stats':
        script  =  'class_stats'
      update_params = []
      for p in params:
        if p in already_computed.keys():
          if p == 'classes':
            update_params.append('this->' + p + '.data()')
          else:
            if already_computed[p] == 'overall_stats':
              update_params.append('this->' + p)
            else:
              update_params.append('this->' + p + '.get()')
        else:
          update_params.append(p)

      utility[s].append((script, output, update_params))
      already_computed[output] = script

  header_script = header_file(dependency)
  hpp_script = hpp_file(dependency)
  cpp_script = cpp_file(utility)

  header_file = os.path.join(directory, 'scorer.h')
  hpp_file = os.path.join(directory, 'scorer.hpp')
  cpp_file = os.path.join(directory, 'scorer.cpp')

  with open(header_file, 'w') as cpp:
    cpp.write(header_script)

  with open(hpp_file, 'w') as cpp:
    cpp.write(hpp_script)

  with open(cpp_file, 'w') as cpp:
    cpp.write(cpp_script)
