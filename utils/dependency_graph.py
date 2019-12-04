#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re
import networkx as nx
from collections import defaultdict

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']


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

  Parameters
  ----------
    script_name: str
      C++ script filename

  Returns
  -------
    dependency: dict
      Dependencies dictionary
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

  Parameters
  ----------
    deps: dict
      Dependencies graph as DAG

  Returns
  -------
    dependency_graph: nx.Digraph
      DAG in NetworkX format
  '''
  dependency_graph = nx.DiGraph(deps)
  # dependency_graph = nx.algorithms.dag.transitive_reduction(dependency_graph)

  useless_func = set(dependency_graph.nodes) - set(deps.keys())
  dependency_graph.remove_nodes_from(useless_func)

  return dependency_graph


def graph_layering (G):
  '''
  Associate each node of the graph G to a layer according to
  its dependencies (modeled by edge connections).

  Parameters
  ----------
    G : NetworkX DiGraph
        A directed acyclic graph (DAG)

  Returns
  -------
    scores : dict()
      A dictionary of vertices in which values are the corresponding
      layer number {vertex : layer-score}
  '''

  with nx.utils.reversed(G):

    # at the beginning they are the root nodes
    zero_indegree = [v for v, d in G.in_degree() if d == 0]

    # initialize the layer-score with 0 for root nodes
    scores = {k : 0 for k in zero_indegree}

    if len(zero_indegree) > 1: # there are multiple roots
      # temporary add a dummy-vertex as absolute root of the graph
      G.add_node('dummy-node')
      G.add_edges_from((('dummy-node', r) for r in zero_indegree))
      zero_indegree = ['dummy-node'] # it is the new root
      scores['dummy-node'] = -1 # useless node layer

    indegree_map = {v : d for v, d in G.in_degree() if d > 0}

    while zero_indegree:

      node = zero_indegree.pop()

      if node not in G:
        raise RuntimeError('Graph changed during iteration')

      for _, child in G.edges(node):
        try:
          indegree_map[child] -= 1
        except KeyError:
          raise RuntimeError('Graph changed during iteration')

        if indegree_map[child] == 0:
          zero_indegree.append(child)
          del indegree_map[child]

      # ancestors of the current node
      ancestors = nx.algorithms.dag.ancestors(G, node)

      if ancestors: # if not it is a root
        # the right layer is the max + 1 of its ancestors
        scores[node] = max((scores[k] for k in ancestors)) + 1

      # remove dummy node if necessary
      if G.has_node('dummy-node'):
        G.remove_node('dummy-node')
        scores.pop('dummy-node')

    return scores


def workflow_net (dep_net, list_deps, src):
  '''
  Extract the position of each node according to the
  graph layering function.
  A dictionary of workflow is given in return with as
  keys the number of processing layer and as values
  the list of function could be computed in parallel

  Parameters
  ----------
    dep_net: nx.DiGraph
      dependency graph as DAG

    list_deps: dict
      dictionary with dependencies
      Key: function name
      Value: list of functions required by the Key-function

    src: dict
      dictionary of dependencies
      Key: function name
      Value: original C++ file in which the function can be found
  '''
  scores = graph_layering(dep_net)

  groups = defaultdict(list)
  for k, score in scores.items():
    groups[score].append((src[k], k, list_deps[k]))

  return dict(groups)




if __name__ == '__main__':

  import os

  directory = os.path.join(os.path.dirname(__file__), '..', 'include/')

  dependency = {hpp : functions_script(directory + hpp) for hpp in ['common_stats.h',
                                                                    'class_stats.h',
                                                                    'overall_stats.h'
                                                                    ]}

  all_deps = dict(pair for d in [v for i,v in dependency.items()] for pair in d.items())

  src = dict()
  for k, v in dependency.items():
    for i in v.keys():
        src[i] = k

  dep_net = dependency_net(all_deps)
  workflow = workflow_net(dep_net, all_deps, src)


