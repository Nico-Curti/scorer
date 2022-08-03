#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re
import networkx as nx
from operator import itemgetter
from collections import Counter
from collections import defaultdict

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']
__all__ = ['functions_script',
           'dependency_net',
           'graph_layering',
           'workflow_net',
           'layering_layout',
          ]

def functions_script (script_name : str) -> dict:
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
  The return dictionary has as key the function name
  (equal to the return name) and as value the list of variable
  needed to compute it.

  Parameters
  ----------
    script_name: str
      C++ script filename

  Returns
  -------
    dependency: dict
      Dependencies dictionary
  '''

  filename = os.path.basename(script_name)

  op = re.compile(r'auto operator\(\)\s+\((.*)')
  name = re.compile(r'\}[\s+]get_(.*);')
  deps = re.compile(r'[&*]\s+(\w+)[,\)]')
  types = re.compile(r'[&*]')
  tags = re.compile(r'struct // (.*)')

  with open(script_name, 'r', encoding='utf-8') as fp:
    code = fp.read()

  operations = op.findall(code)
  names = name.findall(code)

  graph = dict()
  for name, op, tag in zip(names, operations, tags.findall(code)):
    dep = deps.findall(op)
    type = types.findall(op)
    graph[name] = {'dependency': list(zip(dep, type)),
                   'label': tag,
                   'file': filename
                   }

  return graph

def dependency_net (dependency : dict) -> nx.DiGraph:
  '''
  Filter the dependency in relation to the all set of
  functors name found in the c++ script.
  A direct graph is returned to model the dependencies
  of each variable in relation to the available (computable).

  Parameters
  ----------
    dependency: dict
      Dependencies graph as DAG

  Returns
  -------
    dependency_graph: nx.Digraph
      DAG in NetworkX format
  '''
  deps = {name : map(itemgetter(0), var['dependency'])
          for name, var in dependency.items()}
  dependency_graph = nx.DiGraph(deps)

  useless_func = set(dependency_graph.nodes) - set(deps.keys())
  dependency_graph.remove_nodes_from(useless_func)

  return dependency_graph


def graph_layering (G : nx.DiGraph) -> dict:
  '''
  Associate each node of the graph G to a layer
  according to its dependencies (modeled by edge
  connections).

  Parameters
  ----------
    G : NetworkX DiGraph
        A directed acyclic graph (DAG)

  Returns
  -------
    scores : dict()
      A dictionary of vertices in which values are
      the corresponding layer number
      {vertex : layer-score}
  '''

  with nx.utils.reversed(G):

    # at the beginning they are the root nodes
    zero_indegree = [v for v, d in G.in_degree() if d == 0]

    # initialize the layer-score with 0 for root nodes
    scores = {k : 0 for k in zero_indegree}

    # IF there are multiple roots
    if len(zero_indegree) > 1:
      # temporary add a dummy-vertex as absolute root of the graph
      G.add_node('dummy-node')
      G.add_edges_from((('dummy-node', r) for r in zero_indegree))
      # it is the new root
      zero_indegree = ['dummy-node']
      # useless node layer
      scores['dummy-node'] = -1

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


def workflow_net (dep_net : nx.DiGraph, list_deps : dict) -> dict:
  '''
  Extract the positions of each node according to the
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
      Value: list of functions required by the
             Key-function

  Returns
  -------
    groups: dict
      Dictionary of workflow levels.
      For each level the list of scores is stored
      in the values.
  '''
  scores = graph_layering(dep_net)

  groups = defaultdict(list)
  for k, score in scores.items():
    groups[score].append((k, list_deps[k]))

  return dict(groups)


def layering_layout (dep_net : nx.DiGraph, increment : float=1.) -> dict:
  '''
  Extract the coordinates of each node according to the
  graph layering function.
  A dictionary of positions is given in return with as
  keys the node name and as values
  the (x, y) coordinates in the layering layout

  Parameters
  ----------
    dep_net: nx.DiGraph
      dependency graph as DAG

    increment: float
      x coordinate increment

  Returns
  -------
    pos: dict
      Dictionary of node positions.
      The keys are given by the node names and the value
      is a tuple (x, y)
  '''
  scores = graph_layering(dep_net)
  groups = Counter(scores.values())
  seen = Counter()

  pos = {}
  for node, level in scores.items():
    last_x = seen[level]
    pos[node] = (last_x - groups[level] * .5, level)
    seen[level] += increment

  return pos


if __name__ == '__main__':

  directory = os.path.join(os.path.dirname(__file__), '..', 'include/')

  dependency = {}
  for hpp in ('common_stats.h', 'class_stats.h', 'overall_stats.h'):
    dep = functions_script(directory + hpp)
    dependency.update(dep)

  dep_net = dependency_net(dependency)
  workflow = workflow_net(dep_net, dependency)


