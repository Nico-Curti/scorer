#!/usr/bin/python

import re
import pandas as pd
from networkx import DiGraph
from networkx.drawing.nx_pydot import graphviz_layout

def functions_script (script_name):
  '''
  Read the .h script and capture all the functors.
  Pay attention to the sintax of the c++ script:
    - each function must be defined as anonymous struct
      with the overload of operator () with auto as
      return type (since c++11)
    - each function must take as parameter a set of
      variable with a perfect match with others struct
      names (see next point).
    - the struct name must be 'get_' + name of variable
      which returns.
  The return dictionary has as key the function name (equal to the return name)
  and as value the list of variable needed to compute it.
  '''

  dependency = dict()
  with open(script_name, 'r') as f:

    for line in f.readlines():

      if 'auto operator() ' in line:
        link = re.findall('[&*\s]\w+[,\)]', line)
        link = [i[1:-1] for i in link]

      if 'get_' in line:
        function = line.split('_', 1)[-1][:-2]
        dependency[function] = link

  return dependency

def dependency_net (deps):
  '''
  Filter the dependency in relation to the all set of
  functors name found in the c++ script.
  A direct graph is returned to model the dependencies
  of each variable in relation to the available (computable).
  '''

  function = set(deps.keys())
  dependency_graph = DiGraph()

  for func, links in deps.items():
    links = list(set(links).intersection(function))
    dependency_graph.add_edges_from([(func, i) for i in links])

  return dependency_graph


def workflow_net (dep_net, list_deps):
  '''
  Extract the position of each node according to the
  dot layout given by graphviz.
  A dictionary of workflow is given in return with as
  keys the number of processing layer and as values
  the list of function could be computed in parallel


  Note: this step must be re-implemented without graphviz
  considering that in a digraph the source nodes are given
  by the nodes with in-degree equal to zero and that the layers
  of processing are given by the first near nodes following the tree
  structure.
  '''

  pos = graphviz_layout(dep_net, prog='dot')
  pos_df = pd.DataFrame(data=pos).T
  pos_df.columns = ['x', 'y']

  workflow = {i : [(s[:-2], f, d[f]) for s, d in list_deps.items()
              for f in funcs.index if f in d.keys()]
              for i, (y, funcs) in enumerate(pos_df.groupby('y', sort=True))}

  return workflow

if __name__ == '__main__':

  import os

  directory = os.path.join(os.path.dirname(__file__), '..', 'include/')

  dependency = {hpp : functions_script(directory + hpp) for hpp in ['common_stats.h',
                                                                    'class_stats.h',
                                                                    'overall_stats.h'
                                                                    ]}

  all_deps = dict(pair for d in [v for i,v in dependency.items()] for pair in d.items())

  dep_net = dependency_net(all_deps)
  workflow = workflow_net(dep_net, dependency)


