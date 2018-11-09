#!/usr/bin/python

from dependency_graph import functions_script, dependency_net

import pandas as pd
import matplotlib.pyplot as plt
from mpld3 import plugins, save_html
from networkx import draw_networkx_edges, draw_networkx_labels
from networkx.drawing.nx_pydot import graphviz_layout

css = """
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
"""

def draw_network(filename, scripts):

  data = pd.read_csv(filename, sep=',', index_col=0)

  dependency = {hpp : functions_script(hpp) for hpp in scripts}
  all_deps = dict(pair for d in [v for i,v in dependency.items()] for pair in d.items())
  dep_net = dependency_net(all_deps)
  dep_net.remove_node('confusion_matrix')

  pos = graphviz_layout(dep_net, prog='dot')
  dep_net = dep_net.reverse()

  fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(50, 10))
  net = draw_networkx_edges(dep_net, pos=pos, ax=ax, edge_color='lightgray')
  pos_lbl = {n : (x, y + 10) for n, (x, y) in pos.items()}
  lbl = {n : n for n, _ in pos.items()}
  net = draw_networkx_labels(dep_net, pos=pos_lbl, labels=lbl, ax=ax,
                             font_size=20, font_weight='bold', alpha=.8)
  net = ax.scatter(*zip(*pos.values()),
                   marker='o',
                   s=400,
                   color='b',
                   alpha=.6,
                   edgecolors='k',
                   linewidths=0.05
                   )

  labels = [str(data.loc[func].to_frame().to_html()) for func, _ in pos.items()]
  tooltip = plugins.PointHTMLTooltip(net, labels,
                                     voffset=10, hoffset=10, css=css)
  plugins.connect(fig, tooltip)
  save_html(fig, '../img/dependency_graph.html')


if __name__ == '__main__':

  scripts = ['../include/' + hpp for hpp in ['common_stats.h',
                                             'class_stats.h',
                                             #'overall_stats.h'
                                             ]]


  filename = 'cls_stats.csv'

  draw_network(filename, scripts)