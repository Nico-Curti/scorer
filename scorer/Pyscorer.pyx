# distutils: language = c++
# cython: language_level=2

cimport cython
from libcpp.vector cimport vector
from libcpp.memory cimport unique_ptr
from cython.operator cimport dereference as deref
import numpy as np

cdef extern from "scorer.h":
  cppclass scorer:
    scorer() except +

    # Attributes

    vector[float] classes

    unique_ptr[float] confusion_matrix
    unique_ptr[float] TP
    unique_ptr[float] FN
    unique_ptr[float] FP
    unique_ptr[float] TN
    unique_ptr[float] POP
    unique_ptr[float] P
    unique_ptr[float] N
    unique_ptr[float] TOP
    unique_ptr[float] TON
    unique_ptr[float] TPR
    unique_ptr[float] TNR
    unique_ptr[float] PPV
    unique_ptr[float] NPV
    unique_ptr[float] FNR
    unique_ptr[float] FPR
    unique_ptr[float] FDR
    unique_ptr[float] FOR
    unique_ptr[float] ACC
    unique_ptr[float] F1_SCORE
    unique_ptr[float] F05_SCORE
    unique_ptr[float] F2_SCORE
    unique_ptr[float] MCC
    unique_ptr[float] BM
    unique_ptr[float] MK
    unique_ptr[float] PLR
    unique_ptr[float] NLR
    unique_ptr[float] DOR
    unique_ptr[float] PRE
    unique_ptr[float] G
    unique_ptr[float] RACC
    unique_ptr[float] ERR_ACC
    unique_ptr[float] RACCU
    unique_ptr[float] jaccard_index
    unique_ptr[float] IS
    unique_ptr[float] CEN
    unique_ptr[float] MCEN

    float overall_accuracy
    float overall_random_accuracy_unbiased
    float overall_random_accuracy
    float overall_kappa
    float PC_PI
    float PC_AC1
    float PC_S
    float PI
    float AC1
    float S
    float kappa_SE
    float kappa_unbiased
    float kappa_no_prevalence
    float kappa_CI
    float overall_accuracy_se
    float chi_square
    float phi_square
    float cramers_V_calc
    float response_entropy
    float reference_entropy
    float cross_entropy
    float join_entropy
    float conditional_entropy
    float mutual_information
    float kl_divergence
    float lambda_B
    float lambda_A
    float DF
    float overall_jaccard_index
    float hamming_loss
    float zero_one_loss
    float NIR
    float p_value
    float overall_CEN
    float overall_MCEN

    # Methods
    void compute_score(int *, int *, int, int)
    void print_class_stats()
    void print_overall_stats()

cdef class Pyscorer:
  cdef unique_ptr[scorer] thisptr

  cdef public:
    object score, Nclass

  def __cinit__(self):
    self.thisptr.reset(new scorer())

  def __init__(self, lbl_true, lbl_pred):
    cdef int n_lbl = len(lbl_true)
    assert(n_lbl == len(lbl_pred))

    cdef vector[int] cpp_lbl_true = np.asarray(lbl_true, dtype=np.int32)
    cdef vector[int] cpp_lbl_pred = np.asarray(lbl_pred, dtype=np.int32)

    deref(self.thisptr).compute_score(&cpp_lbl_true[0], &cpp_lbl_pred[0], n_lbl, n_lbl)
    self.Nclass = deref(self.thisptr).classes.size()

    self.score = {
              "classes" : deref(self.thisptr).classes,

              "confusion_matrix" : [(deref(self.thisptr).confusion_matrix.get())[i] for i in range(self.Nclass * self.Nclass)],
              "TP" : [(deref(self.thisptr).TP.get())[i] for i in range(self.Nclass)],
              "FN" : [(deref(self.thisptr).FN.get())[i] for i in range(self.Nclass)],
              "FP" : [(deref(self.thisptr).FP.get())[i] for i in range(self.Nclass)],
              "TN" : [(deref(self.thisptr).TN.get())[i] for i in range(self.Nclass)],
              "POP" : [(deref(self.thisptr).POP.get())[i] for i in range(self.Nclass)],
              "P" : [(deref(self.thisptr).P.get())[i] for i in range(self.Nclass)],
              "N" : [(deref(self.thisptr).N.get())[i] for i in range(self.Nclass)],
              "TOP" : [(deref(self.thisptr).TOP.get())[i] for i in range(self.Nclass)],
              "TON" : [(deref(self.thisptr).TON.get())[i] for i in range(self.Nclass)],
              "TPR" : [(deref(self.thisptr).TPR.get())[i] for i in range(self.Nclass)],
              "TNR" : [(deref(self.thisptr).TNR.get())[i] for i in range(self.Nclass)],
              "PPV" : [(deref(self.thisptr).PPV.get())[i] for i in range(self.Nclass)],
              "NPV" : [(deref(self.thisptr).NPV.get())[i] for i in range(self.Nclass)],
              "FNR" : [(deref(self.thisptr).FNR.get())[i] for i in range(self.Nclass)],
              "FPR" : [(deref(self.thisptr).FPR.get())[i] for i in range(self.Nclass)],
              "FDR" : [(deref(self.thisptr).FDR.get())[i] for i in range(self.Nclass)],
              "FOR" : [(deref(self.thisptr).FOR.get())[i] for i in range(self.Nclass)],
              "ACC" : [(deref(self.thisptr).ACC.get())[i] for i in range(self.Nclass)],
              "F1_SCORE" : [(deref(self.thisptr).F1_SCORE.get())[i] for i in range(self.Nclass)],
              "F05_SCORE" : [(deref(self.thisptr).F05_SCORE.get())[i] for i in range(self.Nclass)],
              "F2_SCORE" : [(deref(self.thisptr).F2_SCORE.get())[i] for i in range(self.Nclass)],
              "MCC" : [(deref(self.thisptr).MCC.get())[i] for i in range(self.Nclass)],
              "BM" : [(deref(self.thisptr).BM.get())[i] for i in range(self.Nclass)],
              "MK" : [(deref(self.thisptr).MK.get())[i] for i in range(self.Nclass)],
              "PLR" : [(deref(self.thisptr).PLR.get())[i] for i in range(self.Nclass)],
              "NLR" : [(deref(self.thisptr).NLR.get())[i] for i in range(self.Nclass)],
              "DOR" : [(deref(self.thisptr).DOR.get())[i] for i in range(self.Nclass)],
              "PRE" : [(deref(self.thisptr).PRE.get())[i] for i in range(self.Nclass)],
              "G" : [(deref(self.thisptr).G.get())[i] for i in range(self.Nclass)],
              "RACC" : [(deref(self.thisptr).RACC.get())[i] for i in range(self.Nclass)],
              "ERR_ACC" : [(deref(self.thisptr).ERR_ACC.get())[i] for i in range(self.Nclass)],
              "RACCU" : [(deref(self.thisptr).RACCU.get())[i] for i in range(self.Nclass)],
              "jaccard_index" : [(deref(self.thisptr).jaccard_index.get())[i] for i in range(self.Nclass)],
              "IS" : [(deref(self.thisptr).IS.get())[i] for i in range(self.Nclass)],
              "CEN" : [(deref(self.thisptr).CEN.get())[i] for i in range(self.Nclass)],
              "MCEN" : [(deref(self.thisptr).MCEN.get())[i] for i in range(self.Nclass)],

              "overall_accuracy" : deref(self.thisptr).overall_accuracy,
              "overall_random_accuracy_unbiased" : deref(self.thisptr).overall_random_accuracy_unbiased,
              "overall_random_accuracy" : deref(self.thisptr).overall_random_accuracy,
              "overall_kappa" : deref(self.thisptr).overall_kappa,
              "PC_PI" : deref(self.thisptr).PC_PI,
              "PC_AC1" : deref(self.thisptr).PC_AC1,
              "PC_S" : deref(self.thisptr).PC_S,
              "PI" : deref(self.thisptr).PI,
              "AC1" : deref(self.thisptr).AC1,
              "S" : deref(self.thisptr).S,
              "kappa_SE" : deref(self.thisptr).kappa_SE,
              "kappa_unbiased" : deref(self.thisptr).kappa_unbiased,
              "kappa_no_prevalence" : deref(self.thisptr).kappa_no_prevalence,
              "kappa_CI" : deref(self.thisptr).kappa_CI,
              "overall_accuracy_se" : deref(self.thisptr).overall_accuracy_se,
              "chi_square" : deref(self.thisptr).chi_square,
              "phi_square" : deref(self.thisptr).phi_square,
              "cramers_V_calc" : deref(self.thisptr).cramers_V_calc,
              "response_entropy" : deref(self.thisptr).response_entropy,
              "reference_entropy" : deref(self.thisptr).reference_entropy,
              "cross_entropy" : deref(self.thisptr).cross_entropy,
              "join_entropy" : deref(self.thisptr).join_entropy,
              "conditional_entropy" : deref(self.thisptr).conditional_entropy,
              "mutual_information" : deref(self.thisptr).mutual_information,
              "kl_divergence" : deref(self.thisptr).kl_divergence,
              "lambda_B" : deref(self.thisptr).lambda_B,
              "lambda_A" : deref(self.thisptr).lambda_A,
              "DF" : deref(self.thisptr).DF,
              "overall_jaccard_index" : deref(self.thisptr).overall_jaccard_index,
              "hamming_loss" : deref(self.thisptr).hamming_loss,
              "zero_one_loss" : deref(self.thisptr).zero_one_loss,
              "NIR" : deref(self.thisptr).NIR,
              "p_value" : deref(self.thisptr).p_value,
              "overall_CEN" : deref(self.thisptr).overall_CEN,
              "overall_MCEN" : deref(self.thisptr).overall_MCEN,
            }

  def __repr__(self):
    return '<Pyscorer (classes: ' + str(self.score['classes']) + ')>'

  def __str__(self):
    print('\nClass Statistic : \n\n')
    deref(self.thisptr).print_class_stats()
    print('\n\nOverall Statistic : \n\n')
    deref(self.thisptr).print_overall_stats()
    return '\n'

  def __getitem__(self, stat):
    return self.score[stat]

  def __setitem__(self, stat, values):
    self.score[stat] = values
