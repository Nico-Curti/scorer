---
title: 'scorer: Machine learning scores graph'
tags:
- machine-learning-algorithms
- score-calculator
- confusion-matrix
- statistics
- parallel
- dag
- python3
- cpp
authors:
- name: Nico Curti^[co-first author]
  orcid: 0000-0001-5802-1195
  affiliation: 1
- name: Daniele Dall'Olio^[co-first author]
  orcid: 0000-0003-0196-6870
  affiliation: 3
- name: Riccardo Biondi
  orcid: 0000-0003-0872-7098
  affiliation: 2
- name: Lorenzo Dall'Olio
  orcid: 0000-0002-8907-0034
  affiliation: 3
- name: Daniel Remondini
  orcid: 0000-0003-3185-7456
  affiliation: 3
- name: Gastone Castellani
  orcid: 0000-0003-4892-925X
  affiliation: 2
- name: Enrico Giampieri
  orcid: 0000-0003-2269-2338
  affiliation: 1
affiliations:
- name: eDIMESLab, Department of Experimental, Diagnostic and Specialty Medicine of Bologna University
  index: 1
- name: Department of Experimental, Diagnostic and Specialty Medicine of Bologna University
  index: 2
- name: Department of Physics and Astronomy of Bologna University
  index: 3
date: 14 June 2021
bibliography: paper.bib
---

# Summary

The `Scorer` project implements a `scikit-learn` compatible set of machine-learning metric functions using a factor graph parallel environment.
The user interface of the library is generated fully automatically using a strict language formatting of the backend.
The dependency graph and the optimal parallelization strategy for the job splitting is automatically found in the pre-processing step, which leads to the creation of the library in both `C++` and `Python` language.
The wrap, via `Cython`, of the `C++` APIs guarantees an efficient computational time also in the `Python` applications.
The library provides easily extendible APIs and possible integrations with other projects.

This library has already been widely used in other machine learning applications [@10.21105/joss.02663@, @app11125438@].
The aim of this project is to extend and optimize the original work of Sepand et al. [@10.21105/joss.00729@].

# Statement of need

Performances evaluation is a crucial task in any machine learning application.
In literature can be found different metric functions able to consider only some aspects of the model performances.
Any author chooses the score which better highlights the advantages of its model, and it is difficult to move around this large zoo of metrics.

At this point the main question is: are these scores totally independent one from each other?
The brief answer is simply no.
In the very interesting work of Sepand et al. [@10.21105/joss.00729@], the authors showed how a wide range of these scores can be computed starting from the evaluation of the simple confusion matrix.

Despite the `Python` code provided by Sepand et al. pointed out the presence of links between the mathematical metric functions, their analyses mainly focused on the score evaluation, without any particular interest on the optimization of their computation.
Starting from their work, we analyzed the inter-connections between the mathematical formulas and we extracted the dependency graph between the involved variables.
Considering a metric function as a node, we can connect each of them to the variables required for their evaluation, i.e a *factor graph* [@10.5555/2100584.2100615@].
The focus of our analysis was not on the mathematical formalism of these graphs, but we aimed to analyze the functions' interaction, aiming to implement the most computational efficient solution to the problem.

In the work of Sepand et al. the authors identify 3 classes of functions: common statistics, class statistics and overall statistics.
The analysis of the underlying dependency graph pointed out the strong inter-dependencies of the involved quantities.
By construction, the dependency graph is a direct acyclic network (DAG).
Starting from the root node, i.e the confusion matrix evaluation, and crossing the network up to the leaf nodes, at each step of the percolation, the incoming nodes identify totally independent quantities.
The nodes independence underlies the possibility to compute them in parallel.
Re-interpreting the graph as DAG we can obtain a stratification of the metrics in levels of potential parallel sections.
In our work we identified 7 putative levels of independence, and therefore 7 potential parallel regions for the computation of the full set of metrics.

These considerations leaded us to the development of the `scorer` library.
The `scorer` library is a `C++` porting of the `PyCM` library of Sepand et al. with a `Cython` wrap for the `Python` compatibility.
Following the above considerations, the computation of score functions are performed in parallel according to the 7 levels found.
Using the `section` keywords of OpenMP library, we performed the parallel job management using no-wait tasks.

The extracted graph includes more than 100 different nodes and their manual implementation becomes an hard (and boring) work in `C++`.
Moreover, possible updates of the graph/metrics would lead to a consequential update of the full code (and related parallelization strategy).
For this reason, we required a strict formatting of the `C++` functions' code, allowing an easily parsing of the library information.
With this expedient, we created a fully automated `Python` script which parses the list of functions, it computes the dependency graph and the stratification levels and it gives back a compilable `C++` script with the desired characteristics.
In this way we can guarantee an easy integration and maintenance of the library.

The automated generation of the code is performed for both the `C++` and `Cython` wrap, and automatically managed via the library installation.

# Acknowledgments

The authors acknowledge COMPARE n. 643476 EU Horizon 2020 (EU) Project.

# References
