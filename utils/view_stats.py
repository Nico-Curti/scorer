#!/usr/bin/env python
# -*- coding: utf-8 -*-

from dependency_graph import dependency_net
from dependency_graph import functions_script
from dependency_graph import layering_layout

import pandas as pd
import matplotlib.pyplot as plt
from mpld3 import save_html
from mpld3 import plugins
from networkx import draw_networkx_edges
from networkx import draw_networkx_labels

__author__  = ['Nico Curti']
__email__   = ['nico.curti2@unibo.it']
__all__ = ['draw_network']

css = '''
      table
      {
        border-collapse: collapse;
      }
      th
      {
        color: #ffffff;
        background-color: #000000;
      }
      td
      {
        background-color: #cccccc;
      }
      table, th, td
      {
        font-family:Arial, Helvetica, sans-serif;
        border: 1px solid black;
        text-align: right;
      }
      g.mpld3-xaxis, g.mpld3-xaxis
      {
        display: none;
      }
      g.mpld3-yaxis, g.mpld3-yaxis
      {
        display: none;
      }
'''

def draw_network (filename : str, scripts : str) -> None:
  '''
  Draw statistics network using HTML support.

  Parameters
  ----------
    filename : str
        Filename of the statistics dumped by
        Scorer object

    scripts : str
        Filename of sources c++ scripts in which
        read the statistics dependencies
  '''

  data = pd.read_csv(filename, sep=',', index_col=0, header=None)

  dependency = {}
  for hpp in scripts:
    dep = functions_script(hpp)
    dependency.update(dep)

  dependency.pop('confusion_matrix')

  dep_net = dependency_net(dependency)
  pos = layering_layout(dep_net)

  dep_net = dep_net.reverse()

  fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(30, 10))
  net = draw_networkx_edges(dep_net, pos=pos, ax=ax, edge_color='lightgray')

  pos_lbl = {n : (x, y + 0.1) for n, (x, y) in pos.items()}
  lbl = {n : n for n, _ in pos.items()}

  net = draw_networkx_labels(dep_net, pos=pos_lbl, labels=lbl, ax=ax,
                             font_size=20, font_weight='bold', alpha=1)

  net = ax.scatter(*zip(*pos.values()),
                   marker='o',
                   s=400,
                   color='b',
                   alpha=.6,
                   edgecolors='k',
                   linewidths=0.05,
                   )

  labels = [str(data.loc[dependency[name]['label']].to_frame().to_html())
            for name, _ in pos.items()]
  tooltip = plugins.PointHTMLTooltip(net, labels,
                                     voffset=10, hoffset=10, css=css)
  plugins.connect(fig, tooltip)
  save_html(fig, 'dependency_graph.html')

  return


if __name__ == '__main__':

  import os

  directory = os.path.join(os.path.dirname(__file__), '..', 'include/')
  scripts = [directory + hpp
             for hpp in ('common_stats.h', 'class_stats.h', 'overall_stats.h')]

  filename = 'cls_stats.csv'

  draw_network(filename, scripts)
