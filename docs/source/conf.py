# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import sys

sys.path.insert(0, '/home/ncurti/Code/scorer')

# -- Project information -----------------------------------------------------

project = 'scorer - Multi-class scorer computation library'
copyright = "2020, Nico Curti, Daniele Dall'Olio"
author = "Nico Curti, Daniele Dall'Olio"

# The full version, including alpha/beta/rc tags
release = '2.0.2'

master_doc = 'index'

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ['sphinx.ext.autodoc',
              'sphinx.ext.napoleon',
              'sphinx.ext.viewcode',
              'sphinx.ext.intersphinx',
              #'rst2pdf.pdfbuilder',
              'breathe',
              'nbsphinx',
              'IPython.sphinxext.ipython_console_highlighting',
]

# Add any paths that contain templates here, relative to this directory.
templates_path = []

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', '**.ipynb_checkpoints']

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = []

# -- Options for PDF output --------------------------------------------------

# Grouping the document tree into LaTeX files. List of tuples# (source start file, target name, title, author, documentclass [howto/manual]).
latex_engine = 'xelatex'
latex_documents = [('index', 'scorer.tex', u'scorer - Multi-class scorer computation library', u'Nico Curti', 'manual'),]
latex_show_pagerefs = True
latex_domain_indices = False

pdf_documents = [('index', u'scorer', u'scorer - Multi-class scorer computation library', u'Nico Curti', 'scorer - Multi-class scorer computation library'),]


nbsphinx_input_prompt = 'In [%s]:'
nbsphinx_kernel_name = 'python3'
nbsphinx_output_prompt = 'Out[%s]:'


breathe_projects = {
  'class_stats' : '/home/ncurti/Code/scorer/docs/source/',
  'common_stats' : '/home/ncurti/Code/scorer/docs/source/',
  'overall_stats' : '/home/ncurti/Code/scorer/docs/source/',
  'scorer' : '/home/ncurti/Code/scorer/docs/source/',
  }
