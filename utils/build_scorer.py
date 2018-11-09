#!/usr/bin/python
from dependency_graph import functions_script, dependency_net, workflow_net

def include_lib(lib):
  return '\n'.join(['#include <' + l + '>' for l in lib])

def start_omp():
  return '\n'.join(['#ifdef _OPENMP',
                    '#pragma omp parallel',
                    '\t' + '{',
                    '#endif',
                    '\n'
                    ])
def stop_omp():
  return '\n'.join(['#ifdef _OPENMP',
                    '\t'*2 + '} // end parallel section',
                    '#endif',
                    '\n'
                  ])

def start_omp_section():
  return '\n'.join(['#ifdef _OPENMP',
                    '#pragma omp sections',
#                    '#pragma omp single',
                    '\t'*2 + '{',
                    '#endif',
                    '\n'])

def stop_omp_section():
  return '\n'.join(['#ifdef _OPENMP',
#                    '#pragma omp barrier',
#                    '#pragma omp taskwait',
                    '\t'*2 + '}',
                    '#endif',
                    '\n'])

def parallel_func(member, output, params):
  return '\n'.join(['#ifdef _OPENMP',
                    '#pragma omp section',
#                    '#pragma omp task',
#                    '#pragma omp single nowait',
                    '#endif',
                    '\t'*3 + 'this->' + output + ' = get_' +
                    output + '(' + ', '.join(params) + ');',
                    '\n'
                    ])

def build_scorer(workflow, dep):
  script = '\n'.join(['#ifndef SCORER_H',
                      '#define SCORER_H',
                      '\n'])
  script += include_lib(['memory',
                         'iostream',
                         'iomanip',
                         'fstream',
                         'assert.h',
                         'common_stats.h', 'class_stats.h','overall_stats.h',])
  script += '\n'
  script += '\n'
  struct = '\n'.join(['struct scorer', '{', '\n'])
  costructor = '\tscorer(){};'
  computation = '\n'.join(['\tvoid compute_score(const int *lbl_true, '
                                                'const int *lbl_pred, '
                                                'const int &n_true, '
                                                'const int &n_pred)',
                           '\t{',
                           '\n',
                          ])
  variables = '\n'.join(['\tint Nclass;',
                         '\tstd::vector<float> classes;'
                         '\n'])
  variables += '\tstd::unique_ptr<float[]> '
  variables += ', '.join([f for f in dep['common_stats.h'].keys() if f != 'classes'])
  variables += ', '
  variables += ', '.join([f for f in dep['class_stats.h'].keys()])
  variables += ';\n'
  variables += '\tfloat '
  variables += ', '.join([f for f in dep['overall_stats.h'].keys()])
  variables += ';\n\n'

  script += struct
  script += variables
  script += costructor
  script += '\n'
  script += computation

  script += '#ifdef PYTHONIC\n#ifdef _OPENMP\n#pragma omp parallel\n\t{\n#endif\n#endif\n'

  script += '\t'*2 + 'assert(n_true == n_pred);'
  script += '\n'
  script += '\t'*2 + 'auto n_lbl = n_true;'
  script += '\n'
#  script += start_omp()

  for lv, values in workflow.items():
    script += start_omp_section()
    for (member, output, params) in values:
      script += parallel_func(member, output, params)
    script += stop_omp_section()
    if lv == 0:
      script += '\t'*2 + 'this->Nclass = static_cast<int>(classes.size());\n\n'

#  script += stop_omp()
  script += '#ifdef PYTHONIC\n#ifdef _OPENMP\n\t}\n#endif\n#endif\n'
  script += '\t} // end computation function'
  script += '\n\n'

  script += '\n'.join(['\tvoid print_class_stats()', '\t{', '\n'])

  for f in dep['common_stats.h'].keys():
    if f != 'confusion_matrix':
      script += '\t'*2 + 'std::cout << std::left << std::setw(40) << "' + f + '";\n'
      script += '\t'*2 + 'for (int i = 0; i < this->Nclass; ++i) std::cout << std::setw(20) << ' + f + '[i] << " ";\n'
      script += '\t'*2 + 'std::cout << std::endl;'
      script += '\n'
  for f in dep['class_stats.h'].keys():
    script += '\t'*2 + 'std::cout << std::left << std::setw(40) << "' + f + '";\n'
    script += '\t'*2 + 'for (int i = 0; i < this->Nclass; ++i) std::cout << std::setw(20) << ' + f + '[i] << " ";\n'
    script += '\t'*2 + 'std::cout << std::endl;'
    script += '\n'

  script += '\t} // end print class_stats'
  script += '\n'

  script += '\n'.join(['\tvoid print_overall_stats()', '\t{', '\n'])
  for f in dep['overall_stats.h'].keys():
    script += '\t'*2 + 'std::cout << std::left << std::setw(40) << "' + f + '" << std::setw(20) << ' + f + ' << std::endl;\n'
    script += '\n'

  script += '\t} // end print ovearll_stats'
  script += '\n'


  script += '\n'.join(['\tvoid print()', '\t{', '\n'])
  script += '\n'.join(['\t'*2 + 'print_class_stats();',
                       '\t'*2 + 'std::cout << std::endl;',
                       '\t'*2 + 'print_overall_stats();',
                       '\n'])
  script += '\t} // end print function'
  script += '\n'

  script += '\n'.join(['\tvoid dump(const std::string &filename)', '\t{', '\n'])
  script += '\n'.join(['\t'*2 + 'std::ofstream os(filename + ".cl_stat");',
                       '\t'*2 + 'os << "Stats,";',
                       '\n',
                       ])

  script += '\n'.join(['\t'*2 + 'os.close();',
                       '\t'*2 + 'os.open(filename + "ov_stats");',
                       '\t'*2 + 'os << "Stats,score" << std::endl;',
                       '\n',
                       ])

  script += '\t'*2 + 'os.close();\n'
  script += '\t} // end dump function'
  script += '\n'

  script += '}; // end struct'
  script += '\n\n'
  script += '#endif // SCORER_H'
  script += '\n'

  return script


if __name__ == '__main__':

  directory = '../include/'

  dependency = {hpp : functions_script(directory + hpp) for hpp in ['common_stats.h',
                                                                    'class_stats.h',
                                                                    'overall_stats.h']}

  all_deps = dict(pair for d in [v for i,v in dependency.items()] for pair in d.items())

  dep_net = dependency_net(all_deps)
  workflow = workflow_net(dep_net, dependency)

  utility = {k: [] for k in workflow.keys()}
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

  script = build_scorer(utility, dependency)

  with open('../include/scorer.h', 'w') as cpp:
    cpp.write(script)
